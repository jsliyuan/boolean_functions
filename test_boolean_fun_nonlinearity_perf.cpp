#include <iostream>
#include <time.h>
#include <assert.h>
#include <cassert>

#include "boolean_fun.h"

using namespace std;

int main() {
  clock_t tStart = clock();
  cout << "Computing nl2 for some 8-variable function... (slow)" << endl;
  BooleanFun fn81(8, "x1x2x3x4+x1x4x6x7+x2x3x6x7+x3x4x5x7+x8");
  assert(fn81.nonlinearity(2) == 40);
  cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " sec." << endl;

  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}