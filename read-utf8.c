//
// Created by zakatinstepan on 19.11.2025.
//

#include "read-utf8.h"
#include <stdio.h>
#

int getutf8() {
  int c, l;
  int first_byte = getchar();

  if (first_byte == EOF) return EOF;
  if (first_byte <= 127) return first_byte;

  c = first_byte;

  if (first_byte >= 0b11110000) {
    l = 4;
  }
  else if (first_byte >= 0b11100000) {
    l = 3;
  }
  else {
    l = 2;
  }

  for (int i = 1; i < l; i++) {
    int next_byte = getchar();
    if (next_byte == EOF) return EOF;
    c = (c << 8) | (next_byte & 0xFF);
  }

  return c;
}

void print_utf8_char(int utf8_char) {
  if (utf8_char <= 127) {
    putchar(utf8_char);
  } else {
    int bytes[4];
    int len = 0;

    if (utf8_char > 0xFFFFFF) len = 4;
    else if (utf8_char > 0xFFFF) len = 3;
    else if (utf8_char > 0xFF) len = 2;
    else len = 1;

    for (int i = 0; i < len; i++) {
      bytes[i] = (utf8_char >> (8 * (len - 1 - i))) & 0xFF;
    }

    for (int i = 0; i < len; i++) {
      putchar(bytes[i]);
    }
  }
}