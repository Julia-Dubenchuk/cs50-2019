#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int shift(char c);

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s keyword\n", argv[0]);
        return 1;
    }

    string key = argv[1];

    for(int i = 0, l = strlen(key); i < l; i++)
    {
        int code = (int) key[i];

        if(code < 65 || code > 122 || (code > 90 && code < 97))
        {
            printf("Usage: %s keyword\n", argv[0]);
            return 2;
        }
    }

    string s = get_string("plaintext: ");
    char secret_s[strlen(s)];
    int lkey = strlen(key);
    int j = 0;

    for(int i = 0, l = strlen(s); i < l; i++)
    {
        int code = (int) s[i];

        if (j == lkey)
        {
            j = 0;
        }

        if((code > 64 && code < 91) || (code > 96 && code < 123))
        {
            int k = shift(key[j]);

            if (isupper(s[i]))
            {
                code = (s[i] - 'A' + k) % 26 + 'A';
            } else
            {
                code = (s[i] - 'a' + k) % 26 + 'a';
            }

            j++;
        }

        secret_s[i] = code;

    }

    printf("ciphertext: %s\n", secret_s);
}

int shift(char c)
{
    return tolower(c) - 'a';
}
