#include <stdio.h>

int main(void)
{
    int arr[] = {5, 2, 1, 3, 6, 4};
    int l = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < l - 1; i++)
    {
        int min_index = i;

        for (int j = i + 1; j < l; j++)
        {
            if (arr[min_index] > arr[j])
            {
                min_index = j;
            }
        }

        if (min_index != i)
        {
            int tmp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = tmp;
        }
    }

    printf("Sorted Array: ");
    for (int i = 0; i < l; i++)
    {
        printf("  %i", arr[i]);
    }
    printf("\n");
}
