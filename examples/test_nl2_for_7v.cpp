// This example can be used to test the second-order nonlinearity of any 7-variable Boolean function.
// It is so easy to verify the result.

#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <cassert>
#include <vector>

#include "../boolean_fun.h"
#include "../boolean_fun_decoder.h"

using namespace std;

int main() {

  // Example 1. This example is from "New bounds on the covering radius of the second order Reed-Muller code of length 128" 
  // by Qichun Wang and Pantelimon Stanica.
  // They claim that this 7-variable Boolean function has second-order nonlinearity 40.
  // We double check that it is true.

  BooleanFunDecoder f(7);
  // You can replace the string here with whatever the ANF of 7-variable function which you want to test.
  f.set_anf("x1x2x3 + x1x4x5 + x2x4x6 + x3x5x6 + x4x5x6 + x1x6x7");
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity of f is "<<f.second_order_nonlinearity_Fourquet_Tavernier()<<endl;


  // Example 2. This 7-variable Boolean function is obtained by our experiments.
  // We check this 7-variable Boolean function in the hexadecimal truth table has second-order nonlinearity 40.

  BooleanFunDecoder f1(7);
  // You can replace the string here with whatever the hexadecimal truth table of 7-variable function which you want to test.
  f1.set_truth_table_hex("A893943C97710ED1874C7D2530D9C515");
  f1.set_truth_table_done();
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity of f1 is "<<f1.second_order_nonlinearity_Fourquet_Tavernier()<<endl;
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}