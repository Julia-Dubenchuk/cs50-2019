#include <stdio.h>
#include <math.h>

int main (void)
{
    int arr[] = {6, 7, 8, 9, 10, 11, 14, 15, 17, 19, 22, 23, 25, 28, 30};
    int l = sizeof(arr) / sizeof(arr[0]);
    int target = 16;
    int start = 0;
    int end = l - 1;

    while (end > start)
    {
        int middle = floor((start + end) / 2);

        if (target == arr[middle])
        {
            printf("TRUE\n");
            return 0;
        }

        if (target > arr[middle])
        {
            start = middle + 1;
        } else
        {
            end = middle - 1;
        }
    }

    printf("FALSE\n");
}
