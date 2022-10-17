// This example can be used to test the second-order nonlinearity of any 9-variable Boolean function.
// It need to take several minutes

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
  BooleanFunDecoder f(9);
  // You can replace the string here with whatever the hexadecimal truth table of 9-variable function which you want to test.
  f.set_truth_table_hex("8222242E22412EE72228471828E1E77B242E27874771118D2181E114E8747DB4224E21E72878817B4E77711D111484D42E17881BE71D1444E78B7D447BD4B44E");
  f.set_truth_table_done();
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity is "<<f.second_order_nonlinearity_Fourquet_Tavernier()<<endl;

  // Example 2.
  BooleanFunDecoder f1(9);
  // You can replace the string here with whatever the ANF of 9-variable function which you want to test.
  f1.set_anf("x1x2x3x4x5x6x7x8x9+x6x9");
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity is "<<f1.second_order_nonlinearity_Fourquet_Tavernier()<<endl;


  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}