function insertion_sort(arr: number[]): number[] {
  let arr_sorted = [];

  for (let i = 0, l = arr.length; i < l; i++) {
    let length = arr_sorted.length;

    if (!length) {
      arr_sorted.push(arr[i]);
      continue;
    }

    if (arr[i] > arr_sorted[length - 1]) {
      arr_sorted.push(arr[i]);
      continue;
    }

    for (let j = length - 1; j >= 0; j--) {
      if (arr[i] < arr_sorted[j]) {
        arr_sorted[j+1] = arr_sorted[j];
        arr_sorted[j] = arr[i];
      }
    }
  }

  return arr_sorted;
}

console.log(insertion_sort([5, 2, 1, 3, 6, 4]));
