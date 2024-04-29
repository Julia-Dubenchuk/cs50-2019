#include <stdio.h>

void bubble_sort(int arr[], int length);

int main(void)
{
    int arr[] = {5, 2, 1, 3, 6, 4};
    const int L = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, L);

    printf("Sorted array:\n");

    for (int i = 0; i < L; i++) {
        printf("%i  ", arr[i]);
    }

    printf("\n");
}

void bubble_sort(int arr[], int length)
{
    int swap_counter;
    int reset_counter = 1;

    do {
        swap_counter = 0;

        for (int i = 0; i < length - reset_counter; i++)
        {
            int curr = arr[i];

            if (arr[i] > arr[i + 1])
            {
                arr[i] = arr[i + 1];
                arr[i + 1] = curr;
                swap_counter++;
            }
        }

        reset_counter++;
    } while(swap_counter);
}
