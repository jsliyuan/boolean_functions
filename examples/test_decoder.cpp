// This example can be used to test the second-order nonlinearity of any 10-variable Boolean function.
// It need to take 30 minutes on average.

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
  // Example 1. The example is from paper "An improved list decoding algorithm for the second order Reed-Muller codes and its applications" 
  // by Rafaël Fourquet and Cédric Tavernier.
  // They claim this 10-variable function (trace(x^7)) has second-order nonlinearity 400.

  // It is the first time that the 10-variable Boolean function with second-order nonlinearity 400 was found,
  // and we double check that it is true.
  // For convenience, we transform the expression of this function trace(x^7) into its ANF.
  
  // It takes about 20 minutes.

  /*BooleanFunDecoder f(10);
  // You can replace the string here with whatever the ANF of 10-variable function which you want to test.
  f.set_anf("x9+x8+x7+x7x9+x7x9x10+x7x8+x7x8x10+x7x8x9+x6+x6x9x10+x6x7+x6x7x9+x5+x5x9x10+x5x8+x5x7x10+x5x6x10+x5x6x8+x4+x4x9+x4x8+x4x8x10+x4x8x9+x4x7+x4x7x10+x4x7x9+x4x7x8+x4x6+x4x6x10+x4x6x8+x4x6x7+x4x5+x4x5x8+x3+x3x8+x3x8x9+x3x7x10+x3x7x9+x3x7x8+x3x6+x3x6x9+x3x6x8+x3x6x7+x3x5+x3x5x10+x3x5x9+x3x5x8+x3x5x6+x3x4x6+x3x4x5+x2+x2x8x10+x2x8x9+x2x7+x2x7x10+x2x7x9+x2x7x8+x2x6x7+x2x5+x2x5x9+x2x5x6+x2x4+x2x4x8+x2x3x9+x2x3x8+x2x3x6+x2x3x5+x2x3x4+x1+x1x10+x1x9+x1x9x10+x1x8x10+x1x7+x1x7x10+x1x7x9+x1x6x9+x1x5+x1x5x9+x1x5x8+x1x5x7+x1x4+x1x4x10+x1x4x9+x1x4x8+x1x4x7+x1x4x6+x1x4x5+x1x3x10+x1x3x9+x1x3x5+x1x3x4+x1x2x8+x1x2x7+x1x2x4");
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity of f is "<<f.second_order_nonlinearity_Fourquet_Tavernier()<<endl;*/



  // Example 2. The example is from paper "An improved list decoding algorithm for the second order Reed-Muller codes and its applications" 
  // by Rafaël Fourquet and Cédric Tavernier.
  // They claim this 10-variable function (trace(x^35)) has second-order nonlinearity 400.

  // It is the first time that the 10-variable Boolean function with second-order nonlinearity 400 was found,
  // and we double check that it is true.
  // For convenience, we transform the expression of this function trace(x^35) into its hexadecimal truth table.  
  
  BooleanFunDecoder f1(10);
  // You can replace the string here with whatever the hexadecimal truth table of 10-variable function which you want to test.
  f1.set_truth_table_hex("179C5C4979C0655F95C2E2013E68A336303C0E7B93254F0DD2BB1C25C85ED9995595E3B99D7691C373B8A6DD22D0717AF9CC01912EA6718FADF85F1067B78195B5AF47A5EAAC2821557A67EBC772E071D197C2640AC8CFF6A7E4DC055CFA986A8ED2B53D5EE97D67FA792C2AAAD9B79135DCB452008942B40708118CCC837507");
  f1.set_truth_table_done();
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  if(f1.nl2_at_most(400)==true){
    cout<<"nl2<=400"<<endl;
  }
  else{
    cout<<"excellent!"<<endl;
  }
  //cout<<"The second-order nonlinearity of f1 is "<<f1.second_order_nonlinearity_Fourquet_Tavernier()<<endl;
  
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}