#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;


double balance_update(double initial_balance, double rate_of_return, double contribution) {
  double new_balance;
  new_balance = initial_balance * (1 + rate_of_return / 12) + contribution;
  return new_balance;
}

double monthlybal(int startAge, double initial, retire_info status) {
  int rem = startAge % 12;
  int age = (startAge - rem) / 12;
  double balance = initial;
  for (int i = 0; i < status.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", age, rem, balance);
    balance = balance_update(balance, status.rate_of_return, status.contribution);
    rem += 1;
    if (rem == 12) {
      age += 1;
      rem = 0;
    }
  }
  return balance;
}

void retirement (int startAge, double initial, retire_info working, retire_info retired) {
  double new_balance = monthlybal(startAge, initial, working);
  int newAge = startAge + working.months;
  monthlybal(newAge, new_balance, retired);
}

int main(void) {
  int startAge = 327;
  double savings = 21345.;
  retire_info working;
  working.months = 489;
  working.contribution = 1000.;
  working.rate_of_return = 0.045;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000.;
  retired.rate_of_return = 0.01;

  retirement(startAge, savings, working, retired);

  return 0;
}
