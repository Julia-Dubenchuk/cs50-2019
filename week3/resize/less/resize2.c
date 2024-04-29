/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int n = atoi(argv[1]);

    if (n < 1 || n > 100)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 2;
    }

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int size_row = 0;
    int current_width = bi.biWidth;
    int current_height = abs(bi.biHeight);

    if (n != 1)
    {
        bi.biWidth *= n;
        bi.biHeight *= n;
        size_row = bi.biWidth * sizeof(RGBTRIPLE);

        if (size_row % 4 != 0)
        {
            bi.biSizeImage = (size_row + sizeof(RGBTRIPLE)) * abs(bi.biHeight);
        } else
        {
            bi.biSizeImage = size_row * abs(bi.biHeight);
        }

        bf.bfSize = bi.biSizeImage + bf.bfOffBits;

    }

       // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int curr_padding =  (4 - (current_width * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0; i < current_height; i++)
    {
        RGBTRIPLE row[bi.biWidth];
        int current_pos = 0;

        // iterate over pixels in scanline
        for (int j = 0; j < current_width; j++)
        {
            RGBTRIPLE triple;

            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int k = 0; k < n; k++, current_pos++) {
                row[current_pos] = triple;
            }
        }

        for (int m = 0; m < n; m++) {
            // write RGB triple to outfile
            fwrite(&row, sizeof(row), 1, outptr);

            // then add it back (to demonstrate how)
            if (new_padding)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, curr_padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
