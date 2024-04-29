#include <stdio.h>

void insertion_sort(int arr[], int length);

int main(void)
{
    int arr[] = {5, 2, 1, 3, 6, 4};
    // 24 / 4 = 6
    int length = sizeof(arr) / sizeof(arr[0]);
    printf("sizeof %lu, %lu\n", sizeof(arr), sizeof(arr[0]));

    insertion_sort(arr, length);

    printf("Sorted array:\n");

    for (int i = 0; i < length; i++)
    {
        printf("%i: %i\n", i, arr[i]);
    }
}

void insertion_sort(int arr[], int length)
{
    for (int i = 1; i < length; i++)
        {
            int curr = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > curr)
            {
                arr[j+1] = arr[j];
                j--;
            }

            arr[j + 1] = curr;
        }
}
