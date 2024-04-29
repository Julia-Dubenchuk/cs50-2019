#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long num = get_long("Numder: ");
    int l = floor(log10(num)) + 1;
    int arr[l];
    printf("%i\n", l);

    for(int i = 0; i < l; i++)
    {
        arr[i] = num % 10;
        num = floor(num / 10);

        printf("%i  ", arr[i]);
    }
    printf("\n");

    int sum = 0;
    for(int i = 1; i < l; i += 2)
    {
        arr[i] *= 2;

        if(arr[i] > 9) {
            sum += arr[i] % 10;
            sum += floor(arr[i] / 10);
        } else
        {
            sum += arr[i];
        }
    }

printf("sum1: %i\n", sum);

    for(int i = 0; i < l; i += 2)
    {
        sum += arr[i];
    }

    printf("sum: %i\n", sum);

    if(sum % 10 != 0)
    {
        printf("INVALID\n");
        return 1;
    }

    if(arr[0] == 4)
    {
        printf("VISA\n");
    } else if(arr[0] == 3 && (arr[1] == 4 || arr[1] == 7))
    {
        printf("American Express\n");
    } else if(arr[0] == 5 && arr[1] > 0 && arr[1] < 6)
    {
        printf("MasterCard\n");
    }
}
