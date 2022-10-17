// This example can be used to test the nonlinearity of any 9-variable Boolean function.
// It is so easy to verify the result.

#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <cassert>
#include <vector>

#include "boolean_fun.h"
#include "boolean_fun_decoder.h"

using namespace std;

int main() {
  // Example 1.
  //Initialization
  BooleanFunDecoder f(9);
  // You can replace the string here with whatever the hexadecimal truth table of 9-variable function which you want to test.
  f.set_truth_table_hex("EDE7F92EBBD25CE822C327C7DD0115DF5959A00B093BF17FFAD9A6C3CD29B15E121D12F2474CBA48807532612EDB393E84547B670F492D56930F14BB5365DBDF");
  f.set_truth_table_done();
  // call nonliearity() to compute the nonlinearity.
  cout<<"The nonlinearity is "<<f.nonlinearity()<<endl;


  // Example 2.
  BooleanFunDecoder f1(9);
  // You can replace the string here with whatever the ANF of 9-variable function which you want to test.
  f1.set_anf("x8x9+x7x8+x6x9+x6x8x9+x6x7x8+x6x7x8x9+x5x8+x5x7x9+x5x7x8x9+x5x6+x5x6x9+x5x6x8x9+x5x6x7+x5x6x7x9+x5x6x7x8x9+x4x8x9+x4x7+x4x7x9+x4x7x8+x4x6x9+x4x6x8+x4x6x8x9+x4x6x7x8+x4x6x7x8x9+x4x5+x4x5x9+x4x5x8x9+x4x5x7+x4x5x7x9+x4x5x7x8+x4x5x6x8+x4x5x6x7+x4x5x6x7x9+x4x5x6x7x8+x3x9+x3x8x9+x3x7x9+x3x7x8+x3x6+x3x6x9+x3x6x8+x3x6x7x8+x3x5x9+x3x5x8+x3x5x7x9+x3x5x7x8+x3x5x7x8x9+x3x5x6+x3x5x6x8x9+x3x5x6x7x9+x3x4x8+x3x4x6x8+x3x4x6x7+x3x4x5+x3x4x5x9+x3x4x5x8+x3x4x5x8x9+x3x4x5x7x9+x3x4x5x6+x3x4x5x6x8+x3x4x5x6x7x9+x3x4x5x6x7x8x9+x2x8+x2x7x9+x2x7x8x9+x2x6x9+x2x6x8+x2x6x7+x2x6x7x9+x2x6x7x8+x2x6x7x8x9+x2x5+x2x5x9+x2x5x8+x2x5x8x9+x2x5x7+x2x5x7x8+x2x5x7x8x9+x2x5x6x8+x2x5x6x7+x2x4x8+x2x4x8x9+x2x4x7+x2x4x7x9+x2x4x7x8x9+x2x4x6+x2x4x6x9+x2x4x6x8x9+x2x4x6x7+x2x4x6x7x9+x2x4x6x7x8x9+x2x4x5x9+x2x4x5x8+x2x4x5x7x9+x2x4x5x7x8x9+x2x4x5x6+x2x4x5x6x9+x2x4x5x6x8+x2x4x5x6x8x9+x2x4x5x6x7+x2x4x5x6x7x9+x2x4x5x6x7x8x9+x2x3+x2x3x9+x2x3x8x9+x2x3x7+x2x3x7x9+x2x3x7x8+x2x3x6+x2x3x6x8x9+x2x3x6x7x8+x2x3x5x8+x2x3x5x7+x2x3x5x7x9+x2x3x5x7x8x9+x2x3x5x6+x2x3x5x6x9+x2x3x5x6x7x9+x2x3x4+x2x3x4x8+x2x3x4x7+x2x3x4x7x9+x2x3x4x7x8+x2x3x4x6+x2x3x4x6x9+x2x3x4x6x8x9+x2x3x4x6x7x8+x2x3x4x6x7x8x9+x2x3x4x5x6+x2x3x4x5x6x7x8+x1x8x9+x1x7+x1x7x8+x1x7x8x9+x1x6x7x9+x1x5x9+x1x5x8+x1x5x8x9+x1x5x7+x1x5x7x9+x1x5x7x8x9+x1x5x6+x1x5x6x8+x1x5x6x7+x1x4+x1x4x8+x1x4x8x9+x1x4x7+x1x4x6+x1x4x6x8+x1x4x6x8x9+x1x4x6x7x8+x1x4x6x7x8x9+x1x4x5+x1x4x5x8x9+x1x4x5x7x8+x1x4x5x6x8+x1x4x5x6x7x8x9+x1x3x8+x1x3x8x9+x1x3x7+x1x3x7x8+x1x3x7x8x9+x1x3x6+x1x3x6x8+x1x3x6x8x9+x1x3x6x7x8+x1x3x6x7x8x9+x1x3x5+x1x3x5x9+x1x3x5x7+x1x3x5x7x9+x1x3x5x7x8+x1x3x5x7x8x9+x1x3x5x6+x1x3x5x6x8+x1x3x5x6x8x9+x1x3x5x6x7+x1x3x4x9+x1x3x4x8+x1x3x4x6x8+x1x3x4x5+x1x3x4x5x8x9+x1x3x4x5x7+x1x3x4x5x7x8+x1x3x4x5x7x8x9+x1x3x4x5x6+x1x3x4x5x6x8+x1x3x4x5x6x8x9+x1x3x4x5x6x7+x1x2+x1x2x9+x1x2x7+x1x2x7x9+x1x2x7x8+x1x2x7x8x9+x1x2x6+x1x2x6x9+x1x2x6x8+x1x2x5x9+x1x2x5x8+x1x2x5x6+x1x2x5x6x9+x1x2x5x6x7+x1x2x5x6x7x9+x1x2x5x6x7x8x9+x1x2x4+x1x2x4x7x9+x1x2x4x7x8+x1x2x4x6+x1x2x4x6x9+x1x2x4x6x8+x1x2x4x6x7x8+x1x2x4x5+x1x2x4x5x7+x1x2x4x5x7x9+x1x2x4x5x6x8+x1x2x4x5x6x7x9+x1x2x3x9+x1x2x3x8+x1x2x3x8x9+x1x2x3x7x9+x1x2x3x6x8+x1x2x3x6x7x8x9+x1x2x3x5+x1x2x3x5x9+x1x2x3x5x8+x1x2x3x5x7+x1x2x3x5x7x9+x1x2x3x5x7x8+x1x2x3x5x7x8x9+x1x2x3x5x6x8+x1x2x3x5x6x7x9+x1x2x3x4+x1x2x3x4x8+x1x2x3x4x7x9+x1x2x3x4x7x8x9+x1x2x3x4x6+x1x2x3x4x6x9+x1x2x3x4x6x8+x1x2x3x4x6x7x8+x1x2x3x4x5+x1x2x3x4x5x8x9+x1x2x3x4x5x6x9+x1x2x3x4x5x6x8+x1x2x3x4x5x6x7 ");
  cout<<"The nonlinearity is "<<f1.nonlinearity()<<endl;
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}
