0.  How many colors does each format support?
An 8bit BMP holds 256 colors, but a 24bit BMP can hold 16.8million colors.
GIF has a maximum of 256 colors.
BMP, JPEG, and PNG can be up to 24 bit (16.8million colors)

1.  Which of the formats supports animation?
Gif

2.  What is the difference between lossy and lossless compression?
Lossy makes inexact approximations about the data in the image to save on file
size, but it can degrade the image. Lossless compression will allow you to
perfectly reconstruct the original image, but can be much larger.

3.  Which of these formats is lossy compressed?
Jpeg

4.  What happens, technically speaking, when a file is deleted on a FAT file
system?
The system modifies the filename's first character to signal it has been deleted
and the space can be recycled. Then it moves the file cluster to the hard
drive's "free cluster" area, but doesn't actually do anything with the cluster
itself.

5.  What can someone like you do to ensure (with high probability) that files
you delete cannot be recovered?
Use a tool to write zeros or a random sequance of values in every block of the
hard drive.

6.  What’s stdint.h?
Definitions of several new integer types to enhance the portability of programs.

7.  What’s the point of using uint8_t, uint32_t, int32_t, and uint16_t in a
program?
To set aside a certain amount of memory for an int, as opposed to the normal 4
bytes.

8.  How many bytes is a BYTE, a DWORD, a LONG, and a WORD, respectively?
BYTE = 1 Byte = 8 Bits
DWORD = 4 Bytes = 32 Bits
LONG = 4 Bytes = 32 Bits
WORD = 2 Bytes = 16 Bits

9.  What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP
file be? (Leading bytes used to identify file formats (with high probability)
are generally called "magic numbers.)"
BM

10. What’s the difference between bfSize and biSize?
bfSize - The size, in bytes, of the bitmap file.
biSize - The number of bytes required by the structure.

11. What does it mean if biHeight is negative?
The bitmap is a top-down and its origin is the upper-left corner.

12. What field in BITMAPINFOHEADER specifies the BMP’s color depth
(i.e., bits per pixel)?
biBitCount

13. Why might fopen return NULL in copy.c:37?
The file doesn't exist or can't write.

14. Why is the third argument to fread always 1 in our code?
We are reading the files one struct at a time.

15. What value does copy.c:70 assign padding if bi.biWidth is 3?
3

16. What does fseek do?
Sets your position in the file forward by the offset you specify either from the
beginning of the file, your current position, or the end of the file, whichever
you choose.

17. What is SEEK_CUR?
Your current position in the file.

18. Whodunit?
Jason Hirschhorn
