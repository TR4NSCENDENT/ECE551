#include <stdio.h>

//return the larger value
size_t max(size_t a, size_t b) {
  if (a > b) return a;
  return b;
}

//helper function for maxSeq
size_t helper(int * array, size_t n, size_t inc_n) {
  if (inc_n > n) return inc_n; // stop if impossible to find 
  for (size_t i = 1; i < n; i++) {
    if (array[i - 1] < array[i]) continue; //keep going if increase
    return helper(array + i, n - i, max(i, inc_n)); //restart if not
  }
  //base case (n = 1 or all strictly increase)
  return max(n, inc_n);
}


size_t maxSeq(int * array, size_t n) {
  if (n == 0) return 0; //corner case
  size_t max_n = helper(array, n, 1);
  return max_n;
}
