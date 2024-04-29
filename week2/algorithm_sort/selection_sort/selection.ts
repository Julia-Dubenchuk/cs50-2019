function selection_sort(arr: number[]): number[] {
    for (let i = 0, l = arr.length; i < l - 1; i++) {
      let min_index = i;

      for (let j = i + 1; j < l; j++) {
        if (arr[min_index] > arr[j] ) {
          min_index = j;
        }
      }

      if (min_index !== i) {
        [arr[i], arr[min_index]] = [arr[min_index], arr[i]];
      }
    }

    return arr;
  }

  console.log(selection_sort([5, 2, 1, 3, 6, 4]));

