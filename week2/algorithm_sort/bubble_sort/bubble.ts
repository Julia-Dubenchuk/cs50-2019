function bubble_sort(arr: number[]): number[] {
    let swap_counter: number;
    const L = arr.length;
    let reset_counter = 1;

    do {
      swap_counter = 0;

       for (let i = 0; i < L - reset_counter; i++) {
        let curr = arr[i];

        if (arr[i] > arr[i + 1]) {
            [arr[i], arr[i + 1]] = [arr[i + 1], curr];
            swap_counter++;
        }
      }

      reset_counter++;
    } while (swap_counter);

   return arr;
  }

  console.log(bubble_sort([5, 2, 1, 3, 6, 4]));
