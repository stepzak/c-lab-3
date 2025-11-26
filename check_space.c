//
// Created by zakatinstepan on 24.11.2025.
//

#include "check_space.h"


#define ENQUAD 0x2000
#define HAIR 0x200A
#define NOBREAK 0x00A0

int is_ascii_space(int c) {
    return ('\t' <= c && c <= '\r') || (c == ' ');
}

int is_space(int c) {
    if (is_ascii_space(c)) {
        return 1;
    }

   return ENQUAD <= c && c <= HAIR;

}