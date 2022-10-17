// This example can be used to test the second-order nonlinearity of any 8-variable Boolean function.
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
  BooleanFunDecoder f(8);
  // You can replace the string here with whatever the hexadecimal truth table of 8-variable function which you want to test.
  f.set_truth_table_hex("FDC4C252C20B6708C108019E6B5D31A1D02623B01016B5D94ABC46D52C258915");
  f.set_truth_table_done();
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity is "<<f.second_order_nonlinearity_Fourquet_Tavernier()<<endl;

  // Example 2.
  BooleanFunDecoder f1(8);
  // You can replace the string here with whatever the ANF of 8-variable function which you want to test.
  f1.set_anf("x1x2x3x4+x5x6x7x8");
  cout<<"The nonlinearity is "<<f1.second_order_nonlinearity_Fourquet_Tavernier()<<endl;
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}