#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

char *crypt(const char *key, const char *salt);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s hash\n", argv[0]);
        return 1;
    }

    // 26 lowercase + 26 uppercase + \0 counts as 1 character = 53
    const int l = 53;
    string letters = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string hash = argv[1];
    char password[6];
    char salt[3];
    char key[6] = "\0\0\0\0\0\0";

    memcpy(salt, hash, 2);

    salt[2] = '\0';

    for(int fifth = 0; fifth < l; fifth++)
    {
        for(int fourth = 0; fourth < l; fourth++)
        {
            for(int third = 0; third < l; third++)
            {
                for(int second = 0; second < l; second++)
                {
                    for(int first = 1; first < l; first++)
                    {
                        key[0] = letters[first];
                        key[1] = letters[second];
                        key[2] = letters[third];
                        key[3] = letters[fourth];
                        key[4] = letters[fifth];

                        if (strcmp(crypt(key, salt), hash) == 0)
                        {
                            printf("Key: %s\n", key);
                            return 0;
                        }
                    }
                }
            }
        }
    }

     printf("Password couldn't be cracked!");

     return 2;
}
