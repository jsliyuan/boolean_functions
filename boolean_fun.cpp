#include "boolean_fun.h"

// BooleanFun constructor with parameter (number of variables)
BooleanFun::BooleanFun(int n)
{
  this->n = n;
  truth_table = new bool(1<<n);
}

// BooleanFun destructor
BooleanFun::~BooleanFun()
{
  delete truth_table;
}


// Returns the number of variables.
int BooleanFun::var_num() {
  return n;
}

int BooleanFun::value(int num, ...) {
  if (num != n) {
    return -1;
  }
  va_list valist;

  int dec = 0;
  va_start(valist, num);
  for (int i = 0;  i < num; i ++) {
    dec = dec*2 + va_arg(valist, int);
  }
  va_end(valist);
  return truth_table[dec];
}