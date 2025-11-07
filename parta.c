#include <stdio.h>
#include <ctype.h>

int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        printf("ERROR: No arguments\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        const char *word = argv[i];
        for (int j = 0; word[j] != '\0'; j++) {
            char c = word[j];
            if (c >= 'a' && c <= 'z') {
                c = c - 'a' + 'A';  // manually capitalize
            }
            putchar(c);
        }

        if (i < argc - 1) {
            putchar(','); // separate arguments by commas
        }
    }

    putchar('\n');
    return 0;
}

