function merge_sort(arr: number[]): number[] {
  const L = arr.length;

  if (L < 2) {
    return arr;
  }

  const LEFT_L = Math.floor(L/2);
  const RIGHT_L = L % 2 ? LEFT_L + 1 : LEFT_L;
  let arr_sorted = [];
  let left = [];
  let right = [];

  for (let j = 0; j < RIGHT_L; j++) {
    if (j < LEFT_L) {
      left[j] = arr[j];
    }

    if (j < RIGHT_L) {
      right[j] = arr[LEFT_L + j];
    }
  }

  for (let i = 0; i < LEFT_L - 1; i++) {
    for (let j = i + 1; j < LEFT_L; j++) {
      if (left[i] > left[j]) {
        [left[i], left[j]] = [left[j], left[i]];
      }
    }
  }

  for (let i = 0; i < RIGHT_L - 1; i++) {
    for (let j = i + 1; j < RIGHT_L; j++) {
      if (right[i] > right[j]) {
        [right[i], right[j]] = [right[j], right[i]];
      }
    }
  }

  for (let i = 0; i < LEFT_L; i++) {
    for (let j = 0; j < RIGHT_L; j++) {
      if (!right[j]) {
        continue;
      }

      if (left[i] > right[j]) {
        arr_sorted.push(right[j]);
        right[j] = null;
      } else {
        arr_sorted.push(left[i]);
        left[i] = null;

        if (i === LEFT_L - 1) {
            arr_sorted.push(right[j]);
            right[j] = null;
        }

        break;
      }
    }

    if (left[i]) {
      arr_sorted.push(left[i]);
    }
  }

  return arr_sorted;
}

console.log(merge_sort([5]));
console.log(merge_sort([5, 2]));
console.log(merge_sort([5, 2, 1]));
console.log(merge_sort([5, 2, 1, 3]));
console.log(merge_sort([5, 2, 1, 3, 6]));
console.log(merge_sort([5, 2, 1, 3, 6, 4]));
