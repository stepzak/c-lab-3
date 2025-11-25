//
// Created by zakatinstepan on 24.11.2025.
//

#include "caesar-utf8.h"
#define YO_BIG 0xD081
#define YO_SMALL 0xD191
#define E_BIG 0xD095
#define E_SMALL 0xD0B5
#define A_BIG 0xD090
#define YA_BIG 0xD0AF
#define A_SMALL 0xD0B0
#define YA_SMALL 0xD18F
#define PE_SMALL 0xD0BF
#define ER_SMALL 0xD180

int caesar_cyrillic_utf8(int utf8_char, int shift) {

    if (utf8_char == YO_BIG) {
        utf8_char = E_BIG;
        shift++;
    }
    else if (utf8_char == YO_SMALL) {
        utf8_char = E_SMALL;
        shift++;
    }
    if (A_BIG <= utf8_char && utf8_char <= YA_BIG) {
        if (utf8_char > E_BIG) {
            shift++;
        }
        int pos = utf8_char - A_BIG;
        int new_pos = (pos + shift) % 32;
        return A_BIG + new_pos;
    }
    if (A_SMALL <= utf8_char && utf8_char <= PE_SMALL) {
        if (utf8_char > E_SMALL) {
            shift++;
        }
        int pos = utf8_char - A_SMALL;
        int new_pos = (pos + shift) % 32;
        if (new_pos < 16) {
            return A_SMALL + new_pos;
        }
        new_pos-=16;
        return ER_SMALL + new_pos;
    }
    if (ER_SMALL <= utf8_char && utf8_char <= YA_SMALL) {
        shift++;
        int pos = utf8_char - ER_SMALL;
        int new_pos = (pos + shift) % 32;
        if (new_pos < 16) {
            return ER_SMALL + new_pos;
        }
        new_pos-=16;
        return A_SMALL + new_pos;
    }
    return utf8_char;

}