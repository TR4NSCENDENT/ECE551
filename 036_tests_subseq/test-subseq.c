#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void check(int * array, size_t n, size_t exp_n) {
  size_t size = maxSeq(array, n);
  if (size != exp_n) {
    printf("Test failed on array\n");
    for (int i = 0; i < n; i++){
      printf("%d, ", array[i]);
    }
    printf("\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[5] = {1, 2, 3, 4, 5};
  check(array1, 5, 5);
  check(array1, 0, 0);
  //check(array1, 6, 5);
  check(array1, 3, 3);
  int array2[5] = {1, 1, 1, 1, 1};
  check(array2, 5, 1);
  int array3[5] = {1, 2, 2, 3, 4};
  check(array3, 5, 3);
  int array4[5] = {3, 2, 1, 0, 0};
  check(array4, 5, 1);
  int array5[5] = {-2, -1, 0, -1, -2};
  check(array5, 5, 3);
  check(array5, 2, 2);
  check(array5+2, 3, 1);
  int array6[5] = {1432435, 32794739, 435572890, 0, 0};
  check(array6, 5, 3);
  int array7[1] = {0};
  check(array7, 1, 1);
  int array8[1] = {-1};
  check(array8, 1, 1);
  int array9[999] = {0};
  for (int i = 0; i < 999; i++) {
    array9[i] = i + 1;
  }
  check(array9, 999, 999);
  return EXIT_SUCCESS;
}
