//
// Created by zakatinstepan on 26.11.2025.
//

#ifndef READ_UTF16_H
#define READ_UTF16_H
#include <stdint.h>

#endif //READ_UTF16_H
typedef enum {
    UTF16_LE,
    UTF16_BE
} utf16_encoding_t;
utf16_encoding_t detect_encoding();
uint32_t getutf16(utf16_encoding_t enc);
void print_utf16_char(uint32_t code_point, utf16_encoding_t enc);