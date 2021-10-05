#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* caesar_cipher(char* text, int shift) {
    char* code = (char*)calloc(strlen(text)+1, sizeof(char));
    int i;

    shift %= 26;

    for (i = 0; i < strlen(text); i++) {

        if (text[i] >= 'a' && text[i] <= 'z') {

            if (text[i]+shift >= 128) {
                shift -= 26;
            }

            code[i] = (char)(text[i]+shift);

            if (code[i] < 'a') {
                code[i] += 26;
            } else if (code[i] > 'z') {
                code[i] -= 26;
            }

        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            code[i] = (char)(text[i]+shift);

            if (code[i] < 'A') {
                code[i] += 26;
            } else if (code[i] > 'Z') {
                code[i] -= 26;
            }

        } else {
            code[i] = text[i];
        }
    }

    return code;
}

int caesar_cipher_main()
{
    char text[] = "The quick brown fox jumps over the lazy dog.";
    int shift = 13;
    char *code = caesar_cipher(text, shift);

    printf("%s => ", text );
    printf("%s\n", code );

    free(code);
    return 0;
}

int main()
{
    caesar_cipher_main();
}