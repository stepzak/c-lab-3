//
// Created by zakatinstepan on 26.11.2025.
//

#include "caesar-utf16.h"
#define YO_BIG 0x0401
#define YO_SMALL 0x0451
#define A_SMALL 0x0430
#define YA_SMALL 0x04FF
#define A_BIG 0x0410
#define YA_BIG 0x042F
#define YE_BIG 0x0415
#define YE_SMALL 0x0435

int caesar_utf16(int c, int shift) {
    if (c == YO_BIG) {
        c = YE_BIG;
        shift++;
    }
    else if (c == YO_SMALL) {
        c = YE_SMALL;
        shift++;
    }
    if (A_SMALL <= c && c <= YA_SMALL) {
        if (c > YE_SMALL) {
            shift++;
        }
        int pos = c - A_SMALL;
        int new_pos = (pos + shift) % 32;
        return A_SMALL + new_pos;
    }
    if (A_BIG <= c && c <= YA_BIG) {
        if (c > YE_BIG) {
            shift++;
        }
        int pos = c - A_BIG;
        int new_pos = (pos + shift) % 32;
        return A_BIG + new_pos;
    }

    return c;
}
