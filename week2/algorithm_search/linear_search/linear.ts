function linear_search(arr: number[], target: number): boolean {
    for (let i = 0, l = arr.length; i < l; i++) {
      if (arr[i] === target) {
        return true;
      }
    }

    return false;
  }

  console.log(linear_search([5, 2, 1, 3, 6, 4], 8));
