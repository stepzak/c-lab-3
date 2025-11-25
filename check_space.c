//
// Created by zakatinstepan on 24.11.2025.
//

#include "check_space.h"

#define ENQUAD_8 0xE28080
#define HAIR_8 0xE2808A

#define ENQUAD_16 0x2000
#define HAIR_16 0x200A
#define NOBREAK_16 0x00A0

int is_ascii_space(int c) {
    return ('\t' <= c && c <= '\r') || (c == ' ');
}

int is_utf8_space(int c) {
    if (is_ascii_space(c)) {
        return 1;
    }

   return ENQUAD_8 <= c && c <= HAIR_8;

}

int is_utf16_space(int c) {
    if (is_ascii_space(c)) {
        return 1;
    }
    return (ENQUAD_16 <= c && c <= HAIR_16) || c == NOBREAK_16;
}