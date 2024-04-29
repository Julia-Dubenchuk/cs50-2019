#include <stdio.h>
#include <math.h>

void merge_sort(int arr[], int l);
void merge(int result[], int left[], int l_length, int right[], int r_length);

int main(void)
{
    int arr[] = {5, 2, 1, 3, 6, 4};
    const int L = sizeof(arr) / sizeof(arr[0]);

    merge_sort(arr, L);

    printf("Sorted Array: ");
    for (int i = 0; i < L; i++)
    {
        printf("  %i", arr[i]);
    }
    printf("\n");
}

void merge_sort(int arr[], int L)
{
    if (L > 1) {
        int middle = floor(L / 2);
        int left[middle];
        int right_length = L % 2 ? middle + 1 : middle;
        int right[right_length];

        for (int i = 0; i < middle; i++) {
            left[i] = arr[i];
        }

        int index = 0;
        for (int i = middle; i < L; i++) {
            right[index] = arr[i];
            index++;
        }


        merge_sort(left, middle);
        merge_sort(right, right_length);

        for (int i = 0; i < L; i++)
        {
            for (int j = i + 1; j < L; j++)
            {
                if (arr[i] > arr[j])
                {
                    arr[i] = arr[j];
                    arr[j] = arr[i];
                }
            }
        }


        merge(arr, left, middle, right, right_length);
    }
}

void merge(int result[], int left[], int l_length, int right[], int r_length)
{
    int left_index = 0;
    int right_index = 0;
    int index = 0;

    while (left_index < l_length && right_index < r_length)
    {
        if (left[left_index] > right[right_index])
        {
            result[index] = right[right_index];
            right_index++;
        } else {
            result[index] = left[left_index];
            left_index++;
        }

        index++;
    }

    while (left_index < l_length)
    {
        result[index] = left[left_index];
        left_index++;
        index++;
    }

    while (right_index < r_length)
    {
        result[index] = right[right_index];
        right_index++;
        index++;
    }
}
