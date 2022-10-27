// This example can be used to test the third-order nonlinearity of any 7-variable Boolean function.
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

  // Example 1. The example is from paper "On the covering radius of the third order Reed-Muller code RM(3, 7)" 
  // by Qichun Wang, Chik How Tan and Theo Fanuela Prabowo.
  // They claim this 7-variable function has third-order nonlinearity 20.
  // and we double check that it is true.
  // It takes about 20 minutes.

  BooleanFunDecoder f(7);
  // You can replace the string here with whatever the ANF of 7-variable function which you want to test.
  f.set_anf("x1x2x3x4+x1x4x6x7+x2x3x6x7+x3x4x5x7");
  // call nonlinearity(r) to compute r-order nonlinearity
  cout<<"The third-order nonlinearity of f is "<<f.nonlinearity(3)<<endl;


  // Example 2. The example is from paper "On the covering radius of the third order Reed-Muller code RM(3, 7)" 
  // by Qichun Wang, Chik How Tan and Theo Fanuela Prabowo.
  // They claim this 7-variable function has third-order nonlinearity 20.
  // and we double check that it is true.
  // It takes about 20 minutes.

  BooleanFunDecoder f1(7);
  // You can replace the string here with whatever the hexadecimal truth table of 7-variable function which you want to test.
  f1.set_anf("x1x2x4x5+x1x2x3x6 + x1x3x4x7 + x2x3x5x7 +x2x4x5x7 + x2x4x6x7");
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The third-order nonlinearity f1 is "<<f1.nonlinearity(3)<<endl;
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}