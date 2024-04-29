#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage %s key\n", argv[0]);
        return 1;
    }

    string key = argv[1];
    for(int i = 0, l = strlen(key); i < l; i++)
    {
        int code = (int) key[i];

        if (code < 48 || code > 57)
        {
            printf("Usage: %s key\n", argv[0]);
            return 2;
        }
    }

    int k = atoi(key);

    string s = get_string("plaintext: ");

    char secret_s[strlen(s)];

    for(int i = 0, l = strlen(s); i < l; i++)
    {
        int code = (int) s[i];

        if ((code > 64 && code < 91) || (code > 96 && code < 123))
        {
            code += k;

            while((code > 90 && code < 95) || code > 122)
            {
                code -= 26;
            }
            secret_s[i] = code;
            continue;
        }

        secret_s[i] = s[i];
    }

    printf("ciphertext: %s\n", secret_s);
}
