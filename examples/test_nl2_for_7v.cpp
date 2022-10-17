// This example can be used to test the second-order nonlinearity of any 7-variable Boolean function.
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
  BooleanFunDecoder f(7);
  // You can replace the string here with whatever the ANF of 7-variable function which you want to test.
  f.set_anf("x1x2x3 + x1x4x5 + x2x4x6 + x3x5x6 + x4x5x6 + x1x6x7");
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity is "<<f.second_order_nonlinearity_Fourquet_Tavernier()<<endl;

  // Example 2.
  BooleanFunDecoder f1(7);
  // You can replace the string here with whatever the hexadecimal truth table of 7-variable function which you want to test.
  f1.set_truth_table("402038323D911F292FD6973707FE1AB5");
  f1.set_truth_table_done();
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The third-order nonlinearity is "<<f1.second_order_nonlinearity_Fourquet_Tavernier()<<endl;
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}