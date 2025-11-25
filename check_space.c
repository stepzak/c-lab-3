//
// Created by zakatinstepan on 24.11.2025.
//

#include "check_space.h"
#define ENQUAD 0xE28080
#define HAIR 0xE2808A

int is_utf8_space(int c) {
    if ('\t' <= c && c <= '\r' || c == ' ') {
        return 1;
    }

   if (ENQUAD <= c && c <= HAIR) {
       return 1;
   }
    
    return 0;
}