#include <stdio.h>

int main(void)
{
    int arr[] = {5, 2, 1, 3, 6, 4};
    int l = sizeof(arr) / sizeof(arr[0]);
    int target = 4;

    for (int i = 0; i < l; i++)
    {
        if (arr[i] == target)
        {
            printf("TRUE\n");
            return 0;
        }
    }

    printf("FALSE\n");
}
