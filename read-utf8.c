//
// Created by zakatinstepan on 19.11.2025.
//

#include "read-utf8.h"
#include <stdio.h>
#include <wchar.h>

int getutf8() {
  int c, l;
  int first_byte = getchar();

  if (first_byte == EOF) return EOF;
  if (first_byte <= 127) return first_byte;

  if (first_byte >= 0b11110000) {
    l = 4;
    c = first_byte & 0x07;
  }
  else if (first_byte >= 0b11100000) {
    l = 3;
    c = first_byte & 0x0F;
  }
  else {
    l = 2;
    c = first_byte & 0x1F;
  }
  for (int i = 1; i < l; i++) {
    int next_byte = getchar();
    if (next_byte == EOF) return EOF;
    c = (c << 6) | (next_byte & 0x3F);
  }

  return c;
}

void print_utf8_char(int utf8_char) {
  putwchar(utf8_char);


}