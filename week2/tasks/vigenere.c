#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int shift (char c);

int main (int argc, string argv[]) {
    if (argc == 2) {
        string key = argv[1];

        for (int i = 0; i < strlen(key); i++) {
            int num = (int) key[i];

            if ((num < 65 || num > 90) && (num < 97 || num > 122)) {
               printf("Usage: %s keyword\n", argv[0]);
               return 1;
            }
        }

        string s = get_string("plaintext: ");
        int l = strlen(s);
        int lKey = strlen(key);

        printf("ciphertext: ");

        for (int i = 0, j = 0; i < l; i++) {
            if (j >= lKey) {
                j = 0;
            }

            int k = shift(key[j]);

            if (isupper(s[i])) {
                printf("%c", 'A' + (s[i] - 'A' + k) % 26);
                j++;
            } else if (islower(s[i])) {
                printf("%c", 'a' + (s[i] - 'a' + k) % 26);
                j++;
            } else {
                printf("%c", s[i]);
            }
        }

        printf("\n");

    } else {
        printf("Usage: %s keyword\n", argv[0]);
        return 1;
    }
}

int shift (char c) {
    return tolower(c) - 'a';
}
