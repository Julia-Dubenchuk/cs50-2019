#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover2 file\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    unsigned char buffer[BLOCK_SIZE];
    int count = 0;
    char filename[8];
    FILE *img;

    while (fread(&buffer, BLOCK_SIZE, 1, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8
            && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0)
        {
            count++;

            if (count > 1)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", count - 1);

            img = fopen(filename, "w");
        }

        if (count > 0)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, img);
        }
    }

    fclose(img);
    fclose(file);
}
