#include "function.h"
#include <cstdio>
#include <cmath>

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, 
               Function<int,int> * fn, 
               const char * m): remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

unsigned getMaxmum(int low, int high) {
  //assuming low <= high
  if (high > low) {
    return log2(high - low) + 1; // positive garanteed
  }
  return 1;
}

void check(Function<int,int> * f, 
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned maxInv = getMaxmum(low, high);
  Function<int,int> * testFunc = new CountedIntFn(maxInv, f, mesg);
  int bsearch_ans = binarySearchForZero(testFunc, low, high);
  if (expected_ans != bsearch_ans) {
    if (low == 1000) { printf("Ans is %d\n", bsearch_ans); }
    fprintf(stderr,
            "Failed to find %d between %d and %d in %s\n", 
            expected_ans,
            low,
            high,
            mesg);
    exit(EXIT_FAILURE);
  }
  delete testFunc;
}

class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};

class LinearFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return arg  - 1000;
  }
};

int main() {
  //sin function
  Function<int,int> * sin_t = new SinFunction();
  check(sin_t, 0, 150000, 52359, "sin_t");
  delete sin_t;
  //linear function
  Function<int,int> * linear_t = new LinearFunction();
  check(linear_t, 0, 1001, 1000, "linear_t"); //worst
  check(linear_t, 0, 1000, 999, "linear_t"); //exclusive property
  check(linear_t, 1000, 1500, 1000, "linear_t"); //inclusive property
  check(linear_t, 0, 500, 499, "linear_t"); //all negative
  check(linear_t, 1500, 2000, 1500, "linear_t"); //all positive
  check(linear_t, 1500, 1500, 1500, "linear_t"); //low = high
  check(linear_t, -10000000, 100000, 1000, "linera_t"); //large number
  delete linear_t;
  return 0;
}
