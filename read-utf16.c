//
// Created by zakatinstepan on 26.11.2025.
//

#include "read-utf16.h"
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>


utf16_encoding_t detect_encoding() {
    int b1 = getchar(), b2 = getchar();
    if (b1 == 0xFF && b2 == 0xFE) return UTF16_LE;
    if (b1 == 0xFE && b2 == 0xFF) return UTF16_BE;


    ungetc(b2, stdin);
    ungetc(b1, stdin);
    return UTF16_LE;
}

uint32_t getutf16(utf16_encoding_t enc) {
    int byte1 = getchar();
    if (byte1 == EOF) return 0xFFFFFFFF;

    int byte2 = getchar();
    if (byte2 == EOF) return 0xFFFFFFFF;

    uint16_t first_unit;

    if (enc == UTF16_LE) {
        first_unit = (byte2 << 8) | byte1;
    } else {
        first_unit = (byte1 << 8) | byte2;
    }

    if (first_unit >= 0xD800 && first_unit <= 0xDBFF) {

        int byte3 = getchar();
        if (byte3 == EOF) return 0xFFFFFFFF;

        int byte4 = getchar();
        if (byte4 == EOF) return 0xFFFFFFFF;

        uint16_t second_unit;
        if (enc == UTF16_LE) {
            second_unit = (byte4 << 8) | byte3;
        } else {
            second_unit = (byte3 << 8) | byte4;
        }

        if (second_unit >= 0xDC00 && second_unit <= 0xDFFF) {

            return 0x10000 + ((first_unit - 0xD800) << 10) + (second_unit - 0xDC00);
        }
            return first_unit;
        }

    return first_unit;
}


int is_high_surrogate(uint16_t code_unit) {
    return (code_unit >= 0xD800 && code_unit <= 0xDBFF);
}


int is_low_surrogate(uint16_t code_unit) {
    return (code_unit >= 0xDC00 && code_unit <= 0xDFFF);
}

uint32_t combine_surrogates(uint16_t high, uint16_t low) {
    return 0x10000 + ((high - 0xD800) << 10) + (low - 0xDC00);
}


void split_surrogates(uint32_t code_point, uint16_t *high, uint16_t *low) {
    code_point -= 0x10000;
    *high = (code_point >> 10) + 0xD800;
    *low = (code_point & 0x3FF) + 0xDC00;
}

void print_utf16_char(uint32_t code_point, utf16_encoding_t enc) {
    if (code_point == 0xFFFFFFFF) return;

    if (code_point <= 0xFFFF) {
        if (enc == UTF16_LE) {
            putwchar(code_point);
        } else {
            putwchar(code_point);
        }
    } else {
        uint16_t high, low;
        split_surrogates(code_point, &high, &low);
        if (enc == UTF16_LE) {
            putwchar(high);
            putwchar(low);
        } else {
            putwchar(high);
            putwchar(low);
        }

    }
}