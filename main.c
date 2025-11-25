#include <ctype.h>
#include <locale.h>
#include <stdio.h>

#include "caesar.h"
#include "check_space.h"
#include "read.h"

void utf8() {
    int state = 0;
    int c = getutf8();
    do {

        if (is_utf8_space(c)) {
            state = 0;
            print_utf8_char(c);
            c = getutf8();
            continue;
        }
        state++;
        int shifted = caesar_cyrillic_utf8(c, state+3);
        print_utf8_char(shifted);
        c = getutf8();

    } while (c != EOF);
}


int main() {

    utf8();
    return 0;
}
