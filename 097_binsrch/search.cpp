#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (high - low <= 1) { return low; }
  int mid = (high + low) / 2;
  int fx = f->invoke(mid);
  if (fx <= 0) { 
    return binarySearchForZero(f, mid, high);
  }
  else {
    return binarySearchForZero(f, low, mid);
  }
}
