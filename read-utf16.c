//
// Created by zakatinstepan on 26.11.2025.
//

#include "read-utf16.h"
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>
#define UNICODE_BMP_MAX 0xFFFF
#define UNICODE_SURROGATE_OFFSET 0x10000
#define UNICODE_HIGH_SURROGATE_START 0xD800
#define UNICODE_HIGH_SURROGATE_END 0xDBFF
#define UNICODE_LOW_SURROGATE_START 0xDC00
#define UNICODE_LOW_SURROGATE_END 0xDFFF
#define SURROGATE_MASK 0x3FF
#define ERROR_CODE 0xFFFFFFFF

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
    if (byte1 == EOF) return ERROR_CODE;

    int byte2 = getchar();
    if (byte2 == EOF) return ERROR_CODE;

    uint16_t first_unit;

    if (enc == UTF16_LE) {
        first_unit = (byte2 << 8) | byte1;
    } else {
        first_unit = (byte1 << 8) | byte2;
    }

    if (first_unit >= UNICODE_HIGH_SURROGATE_START && first_unit <= UNICODE_HIGH_SURROGATE_END) {
        int byte3 = getchar();
        if (byte3 == EOF) return ERROR_CODE;

        int byte4 = getchar();
        if (byte4 == EOF) return ERROR_CODE;

        uint16_t second_unit;
        if (enc == UTF16_LE) {
            second_unit = (byte4 << 8) | byte3;
        } else {
            second_unit = (byte3 << 8) | byte4;
        }

        if (second_unit >= UNICODE_LOW_SURROGATE_START && second_unit <= UNICODE_LOW_SURROGATE_END) {
            return UNICODE_SURROGATE_OFFSET + ((first_unit - UNICODE_HIGH_SURROGATE_START) << 10) + (second_unit - UNICODE_LOW_SURROGATE_START);
        }
        return first_unit;
    }

    return first_unit;
}

int is_high_surrogate(uint16_t code_unit) {
    return (code_unit >= UNICODE_HIGH_SURROGATE_START && code_unit <= UNICODE_HIGH_SURROGATE_END);
}

int is_low_surrogate(uint16_t code_unit) {
    return (code_unit >= UNICODE_LOW_SURROGATE_START && code_unit <= UNICODE_LOW_SURROGATE_END);
}

uint32_t combine_surrogates(uint16_t high, uint16_t low) {
    return UNICODE_SURROGATE_OFFSET + ((high - UNICODE_HIGH_SURROGATE_START) << 10) + (low - UNICODE_LOW_SURROGATE_START);
}

void split_surrogates(uint32_t code_point, uint16_t *high, uint16_t *low) {
    code_point -= UNICODE_SURROGATE_OFFSET;
    *high = (code_point >> 10) + UNICODE_HIGH_SURROGATE_START;
    *low = (code_point & SURROGATE_MASK) + UNICODE_LOW_SURROGATE_START;
}

void print_utf16_char(uint32_t code_point, utf16_encoding_t enc) {
    if (code_point == ERROR_CODE) return;

    if (code_point <= UNICODE_BMP_MAX) {
        putwchar(code_point);
    } else {
        uint16_t high, low;
        split_surrogates(code_point, &high, &low);
        putwchar(high);
        putwchar(low);
    }
}