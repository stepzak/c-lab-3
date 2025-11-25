//
// Created by zakatinstepan on 24.11.2025.
//

#include "caesar.h"
#define YO_BIG 0xD081
#define YO_SMALL 0xD191
#define E_BIG 0xD095
#define E_SMALL 0xD0B5
#define A_BIG 0xD090
#define YA_BIG 0xD0AF
#define A_SMALL 0xD0B0
#define YA_SMALL 0xD18F


int caesar_cyrillic_utf8(int utf8_char, int shift) {

    if (utf8_char == YO_BIG) {
        utf8_char = E_BIG;
        shift++;
    }
    else if (utf8_char == YO_SMALL) {
        utf8_char = E_SMALL;
        shift++;
    }
    int byte1 = (utf8_char >> 8) & 0xFF;
    int byte2 = utf8_char & 0xFF;



    if (byte1 == 0xD0) {
        if (byte2 >= 0x90 && byte2 <= 0xAF) {
            if (byte2 >= 0x96) {
                shift++;
            }
            int pos = byte2 - 0x90;
            int new_pos = (pos + shift) % 32;
            return 0xD090 + new_pos;

        }
        if (byte2 >= 0xB0 && byte2 <= 0xBF) {
            if (byte2 >= 0xB6) {
                shift++;
            }
            int pos = byte2 - 0xB0;
            int new_pos = (pos + shift) % 32;
            if (new_pos < 16) {
                return 0xD0B0 + new_pos;
            }
            return 0xD180 + (new_pos - 16);

        }
    }
    else if (byte1 == 0xD1 && byte2 >= 0x80 && byte2 <= 0x8F) {
        shift++;
        int pos = byte2 - 0x80 + 16;
        int new_pos = (pos + shift) % 32;
        if (new_pos < 16) {

            return 0xD0B0 + new_pos;
        }
        return 0xD180 + (new_pos - 16);

    }

    return utf8_char;
}