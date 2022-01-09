#include <iostream>

#include "boolean_fun.h"

using namespace std;

int main() {
  BooleanFun f(6);
  assert(f.var_num() == 6);

  assert(f.value(4, 0,0,0,0) == -1);

  assert(f.value(6, 0,0,1,1,1,1) == 0);

  cout << "Everything looks good. End of test." << endl;
  return 0;
}