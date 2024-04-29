#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ,/resize f infile outfile\n");
        return 1;
    }

    float f = atof(argv[1]);

    while (f <= 0 || f > 100)
    {
        printf("Usage: ,/resize f infile outfile\n");
        return 2;
    }

    char *infile = argv[2];
    char *outfile = argv[3];

    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    FILE *outptr = fopen(outfile, "w");

    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 1;
    }

    BITMAPFILEHEADER in_bf, out_bf;
    fread(&in_bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER in_bi, out_bi;
    fread(&in_bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Get Original file's padding
    int oldPadding =  (4 - (in_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    out_bf = in_bf;
    out_bi = in_bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (out_bf.bfType != 0x4d42 || out_bf.bfOffBits != 54 || out_bi.biSize != 40 ||
        out_bi.biBitCount != 24 || out_bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Update width, and height in Bitmap info header
    out_bi.biWidth = floor(out_bi.biWidth * f);
    out_bi.biHeight *= ceil(out_bi.biHeight * f);

    // determine padding for scanlines
    int newPadding =  (4 - (out_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Update size in Bitmap info header
    out_bi.biSizeImage = out_bi.biWidth * abs(out_bi.biHeight) *
        sizeof(RGBTRIPLE) + newPadding * abs(out_bi.biHeight);

    // Update Size in Bitmap File Header
    out_bf.bfSize = out_bf.bfOffBits + out_bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int current_row = 0;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(in_bi.biHeight); i < biHeight; i++)
    {
        // Setup array to store pixels in
        RGBTRIPLE row[out_bi.biWidth];
        int current_pixel = 0;

        // iterate over pixels in scanline
        for (int k = 0; k < in_bi.biWidth; k++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            if (f > 1)
            {
                // Repeat each pixel n times
                for (int m = 0; m < ceil(f) && current_pixel < out_bi.biWidth; m++, current_pixel++)
                {
                    row[current_pixel] = triple;
                }
            } else
            {
                if (k % (int) (1 / f) == 0 && current_pixel < out_bi.biWidth)
                {
                    row[current_pixel] = triple;
                    current_pixel++;
                }
            }
        }

        if (f > 1)
        {
            // repeat each row n times
            for (int j = 0; j < ceil(f) && current_row < abs(out_bi.biHeight); j++, current_row++)
            {
                // Write row to out file
                fwrite(&row, sizeof(row), 1, outptr);

                // Add padding to new file
                for (int p = 0; p < newPadding; p++)
                {
                    fputc(0x00, outptr);
                }
            }
        } else
        {
            if (i % (int) (1 / f) == 0 && current_row < abs(out_bi.biHeight))
            {
                // Write row to out file
                fwrite(&row, sizeof(row), 1, outptr);

                current_row++;

                // Add padding to new file
                for (int p = 0; p < newPadding; p++)
                {
                    fputc(0x00, outptr);
                }
            }
        }

        // skip over padding in old file, if any
        fseek(inptr, oldPadding, SEEK_CUR);
    }

    fclose(inptr);
    fclose(outptr);

    return 0;
}
