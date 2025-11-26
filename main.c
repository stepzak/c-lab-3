#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "caesar.h"
#include "check_space.h"
#include "read-utf16.h"
#include "read-utf8.h"

void utf8() {
    int state = 0;
    int c = getutf8();
    do {

        if (is_space(c)) {
            state = 0;
            print_utf8_char(c);
            c = getutf8();
            continue;
        }
        state++;
        int shifted = caesar(c, state+3);
        print_utf8_char(shifted);
        c = getutf8();

    } while (c != EOF);
}

void utf16() {
    int state = 0;
    utf16_encoding_t enc = detect_encoding();
    int c = getutf16(enc);
    do {
        if (is_space(c)) {
            state = 0;
            putwchar(c);
            c = getutf16(enc);
            continue;
        }
        state++;
        int shifted = caesar(c, state+3);
        print_utf16_char(shifted, enc);
        c = getutf16(enc);
    } while (c != EOF);
}

void print_help(const char *program_name) {
    printf("Использование: %s [РЕЖИМ]\n", program_name);
    printf("Режимы:\n");
    printf("--utf8:       Обработка UTF-8 (по умолчанию)\n");
    printf("--utf16:      Обработка UTF-16\n");
    printf("  -h, --help: Показать эту справку\n");

}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "en_US.UTF-8");
    int mode_utf8 = 1;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--utf8") == 0) {
            mode_utf8 = 1;
        } else if (strcmp(argv[i], "--utf16") == 0) {
            mode_utf8 = 0;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        }
    }
    if (mode_utf8) {
        utf8();
    }
    else {
        utf16();
    }

    return 0;
}
