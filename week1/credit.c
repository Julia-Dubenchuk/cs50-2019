#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    long num;
    int sum = 0;
    int oddSum = 0;

    do {
        num = get_long("Number: ");
    } while(num <= 0);

    int length = floor(log10(labs(num))) + 1;
    int digits[length];
    int digits2[length];

    for (int i = length - 1; i >= 0; i--) {
        digits[i] = num % 10;
        num = floor(num / 10);
    }

    for (int i = 0, j = length - 2; j >=0; i++, j-=2) {
        digits2[i] = digits[j] * 2;
    }

    for (int i = 0; i < length / 2; i++) {
        if (digits2[i] > 9) {
            sum += (floor(digits2[i] / 10) + (digits2[i] % 10));
        } else {
            sum += digits2[i];
        }
    }

    for (int i = length - 1; i >= 0; i -= 2) {
        oddSum += digits[i];
    }

    int total = sum + oddSum;

    if (length > 10 && total % 10 == 0) {

        switch(digits[0]) {
            case 3:
                if (digits[1] == 4 || digits[1] == 7) {
                    printf("AMEX\n");
                } else {
                     printf("INVALID\n");
                }

                break;
            case 4:
                printf("VISA\n");
                break;
            case 5:
                if (digits[1] > 0 && digits[1] < 6) {
                    printf("MASTERCARD\n");
                } else {
                     printf("INVALID\n");
                }

                break;
        }
    } else {
        printf("INVALID\n");
    }

}
