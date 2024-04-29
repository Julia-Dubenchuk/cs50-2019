#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    char *cardfile = argv[1];
    FILE *inptr = fopen(cardfile, "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", cardfile);
        return 2;
    }

    unsigned char buffer[512];
    int counter = 0;
    char title[10];
    FILE *img;

    while (fread(&buffer, 512, 1, inptr))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >> 4 == 0xe)
        {
            counter++;

            if (counter > 1)
            {
                fclose(img);
            }

            sprintf(title, "%03d.jpg", counter - 1);
            img = fopen(title, "a");
        }

        if (counter > 0)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }

    fclose(img);
    fclose(inptr);
}
