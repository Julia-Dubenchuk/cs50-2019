function binary_search(arr: number[], target: number): boolean {
    let l = arr.length;
    let start = 0;
    let end = l - 1;

    for (let i = 0; i < l - 1; i++) {
      let min_index = i;

      for (let j = i + 1; j < l; j++) {
        if (arr[min_index] > arr[j]) {
          min_index = j;
        }
      }

      if (min_index !== i) {
        [arr[i], arr[min_index]] = [arr[min_index], arr[i]];
      }
    }

    while (end > start) {
      let middle = Math.floor((start + end) / 2);

      if (arr[middle] === target) {
        return true;
      }

      if (target > arr[middle]) {
        start = middle + 1;
      } else {
        end = middle - 1;
      }
    }

    return false;
  }

  console.log(binary_search([11, 23, 8, 14, 30, 9, 6, 17, 22, 28, 25, 15, 7, 10, 19], 16));
