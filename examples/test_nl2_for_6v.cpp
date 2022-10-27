// This example can be used to test the second-order nonlinearity of any 6-variable Boolean function.
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
  // Example 1. The example is from paper "The Second Order Reed-Muller Code of Length 64 Has Covering Radius 18" by JAMES R. SCHATZ. 
  // They claim this 6-variable function has second-order nonlinearity 18.

  // It is the first time that the 6-variable Boolean function with second-order nonlinearity 18 was found,
  // and we double check that it is true.

  BooleanFunDecoder f(6);
  // You can replace the string here with whatever the ANF of 6-variable function which you want to test.
  f.set_anf("x2x3x6+x2x4x6+x3x5x6+x1x2x3+x1x4x5");
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity of f is "<<f.second_order_nonlinearity_Fourquet_Tavernier()<<endl;


  // Example 2. The example is obtained by our experiment.
  // We check this 6-variable Boolean function in the hexadecimal truth table has second-order nonlinearity 18.

  BooleanFunDecoder f1(6);
  // You can replace the string here with whatever the hexadecimal truth table of 6-variable function which you want to test.
  f1.set_truth_table_hex("D450551244560628");
  f1.set_truth_table_done();
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity of f1 is "<<f1.second_order_nonlinearity_Fourquet_Tavernier()<<endl;
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}