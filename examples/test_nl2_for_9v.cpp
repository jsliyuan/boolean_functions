// This example can be used to test the second-order nonlinearity of any 9-variable Boolean function.
// It need to take several minutes

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
  // Example 1. The example is from paper "Classification of Boolean cubic forms of nine variables" 
  // by Eric Brier and Philippe Langevin.
  // They claim this 9-variable function has second-order nonlinearity 196.

  // It is the first time that the 9-variable Boolean function with second-order nonlinearity 196 was found,
  // and we double check that it is true.
  // It takes about 5 minutes.

  BooleanFunDecoder f(9);
  // You can replace the string here with whatever the ANF of 9-variable function which you want to test.
  f.set_anf("x1x2x3+x4x5x6+x1x4x7+x2x5x7+x3x4x8+x2x6x8+x2x7x8+x3x5x9+x1x6x9+x5x6x9+x7x8x9");
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity of f is "<<f.second_order_nonlinearity_Fourquet_Tavernier()<<endl;

  
  // Example 2. The example is from paper "An improved list decoding algorithm for the second order Reed-Muller codes and its applications" 
  // by Rafaël Fourquet and Cédric Tavernier.
  // They claim this 9-variable function (trace(x^73)) has second-order nonlinearity 196.
  // and we double check that it is true.
  // For convenience, we transform the expression of this function trace(x^7) into its hexadecimal truth table.
  // It takes about 7 minutes.

  BooleanFunDecoder f1(9);
  // You can replace the string here with whatever the hexadecimal truth table of 9-variable function which you want to test.
  f1.set_truth_table_hex("7FFBFEDFFBBCB6ABFE8A8FA1DF689D8FFBE985CDD5FB9813B6AB3880C2E380FBFEDFE992D032F4B3E637FE8A9280460EDF68C8DA5BD08051F44CEC0ED551FEDF");
  f1.set_truth_table_done();
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity of f1 is "<<f1.second_order_nonlinearity_Fourquet_Tavernier()<<endl;

  
  // Example 3. This 9-variable Boolean function is obtained by our experiment.
  // We check that this function has second-order nonlinearity 196.
  // It takes about 80 seconds.

  BooleanFunDecoder f2(9);
  f2.set_truth_table_hex("8222242E22412EE72228471828E1E77B242E27874771118D2181E114E8747DB4224E21E72878817B4E77711D111484D42E17881BE71D1444E78B7D447BD4B44E");
  f2.set_truth_table_done();
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity of f2 is "<<f2.second_order_nonlinearity_Fourquet_Tavernier()<<endl;
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}