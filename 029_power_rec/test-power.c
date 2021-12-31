#include <stdio.h>
#include <stdlib.h>

typedef unsigned pn; //positive number

pn power (pn x, pn y);

void run_check (pn x, pn y, pn expected_ans) {
  pn test_ans = power(x, y);
  if (test_ans != expected_ans) {
    printf("%d ^ %d = %d, but test gives %d. Test Fail\n", x, y, expected_ans, test_ans);
    exit(EXIT_FAILURE);
  }
}

pn correct_power (pn x, pn y) {
  if (y == 0) return 1;
  return x * correct_power(x, y-1);
}

void test (pn x, pn y) {
  pn expected_ans = correct_power(x, y);
  run_check(x, y, expected_ans);
  printf("%d ^ %d = %d. Test Pass\n", x, y, expected_ans);
}
  
int main(void) {
  //test(1, 1);
  //test(0, 1);
  //test(1, 0);
  test(0, 0);
  test(10, 5);
  //test(2, 30);
  return EXIT_SUCCESS;
}
  
