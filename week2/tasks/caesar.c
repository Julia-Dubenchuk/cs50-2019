#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, string argv[]) {
    if (argc == 2) {
        string key = argv[1];

        for (int i = 0; i < strlen(key); i++) {
            int num = (int) key[i];

            if (num < 48 || num > 57) {
               printf("Usage: %s key\n", argv[0]);
               return 0;
            }
        }

        string s = get_string("plaintext: ");
        int k = atoi(key);

        printf("ciphertext: ");

        for (int i = 0; i < strlen(s); i++) {
            int num = (int) s[i];

            if ((num > 64 && num < 91) || (num > 96 && num < 123)) {
                num += k;
            }

            while (num > 122) {
                num -= 26;
            }

            printf("%c", num);
        }

        printf("\n");

    } else {
        printf("Usage: %s key\n", argv[0]);
    }
}
