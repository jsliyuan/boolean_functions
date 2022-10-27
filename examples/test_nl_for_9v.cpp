// This example can be used to test the nonlinearity of any 9-variable Boolean function.
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
  // Example 1. The example is from paper "Search for Boolean Functions With Excellent Profiles in the Rotation Symmetric Class"
  // by Selçuk Kavut, Subhamoy Maitra, and Melek D. Yücel. 
  // They claim this 9-variable function in the hexadecimal truth table form has nonlinearity 241.

  // It is the first time that the 9-variable Boolean function with nonlinearity 241 was found,
  // and we double check that it is true.
  
  //Initialization
  BooleanFun f(9);
  // You can replace the string here with whatever the hexadecimal truth table of 9-variable function which you want to test.
  f.set_truth_table_hex("977F3FFA0EFAAEC955F8FACDCCA9A0837666EBC0FA88E0B3F4E08983C845915E7F7C2C29FCCBA101EA98C085E8118B5EFE21E9118483851EE1952136971676E9");
  f.set_truth_table_done();
  // call nonliearity() to compute the nonlinearity.
  cout<<"The nonlinearity of f is "<<f.nonlinearity()<<endl;


  // Example 2. The example is from paper "9-variable Boolean functions with nonlinearity 242 in the generalized rotation symmetric class"
  // by Selçuk Kavut and Melek Diker Yücel.
  // They claim this 9-variable function in the hexadecimal truth table form has nonlinearity 242.

  // It is the first time that the 9-variable Boolean function with nonlinearity 242 was found,
  // and we double check that it is true.

  BooleanFun f1(9);
  // You can replace the string here with whatever the hexadecimal truth table of 9-variable function which you want to test.
  f1.set_truth_table_hex("125425D30A398F36508C06817BEE122E250D973314F976AED58A3EA9120DA4FE0E4D4575C42DD0426365EBA7FC5F45BE9B2F336981B5E1863618F49474F6FE00");
  f1.set_truth_table_done();
  cout<<"The nonlinearity of f1 is "<<f1.nonlinearity()<<endl;


  // Example 3. The example is obtained by our experiments. 
  // We check this 9-variable Boolean function has nonlinearity 242.
  BooleanFun f2(9);
  // You can replace the string here with whatever the ANF of 9-variable function which you want to test.
  f2.set_anf("x8x9+x7x8+x6x9+x6x8x9+x6x7x8+x6x7x8x9+x5x8+x5x7x9+x5x7x8x9+x5x6+x5x6x9+x5x6x8x9+x5x6x7+x5x6x7x9+x5x6x7x8x9+x4x8x9+x4x7+x4x7x9+x4x7x8+x4x6x9+x4x6x8+x4x6x8x9+x4x6x7x8+x4x6x7x8x9+x4x5+x4x5x9+x4x5x8x9+x4x5x7+x4x5x7x9+x4x5x7x8+x4x5x6x8+x4x5x6x7+x4x5x6x7x9+x4x5x6x7x8+x3x9+x3x8x9+x3x7x9+x3x7x8+x3x6+x3x6x9+x3x6x8+x3x6x7x8+x3x5x9+x3x5x8+x3x5x7x9+x3x5x7x8+x3x5x7x8x9+x3x5x6+x3x5x6x8x9+x3x5x6x7x9+x3x4x8+x3x4x6x8+x3x4x6x7+x3x4x5+x3x4x5x9+x3x4x5x8+x3x4x5x8x9+x3x4x5x7x9+x3x4x5x6+x3x4x5x6x8+x3x4x5x6x7x9+x3x4x5x6x7x8x9+x2x8+x2x7x9+x2x7x8x9+x2x6x9+x2x6x8+x2x6x7+x2x6x7x9+x2x6x7x8+x2x6x7x8x9+x2x5+x2x5x9+x2x5x8+x2x5x8x9+x2x5x7+x2x5x7x8+x2x5x7x8x9+x2x5x6x8+x2x5x6x7+x2x4x8+x2x4x8x9+x2x4x7+x2x4x7x9+x2x4x7x8x9+x2x4x6+x2x4x6x9+x2x4x6x8x9+x2x4x6x7+x2x4x6x7x9+x2x4x6x7x8x9+x2x4x5x9+x2x4x5x8+x2x4x5x7x9+x2x4x5x7x8x9+x2x4x5x6+x2x4x5x6x9+x2x4x5x6x8+x2x4x5x6x8x9+x2x4x5x6x7+x2x4x5x6x7x9+x2x4x5x6x7x8x9+x2x3+x2x3x9+x2x3x8x9+x2x3x7+x2x3x7x9+x2x3x7x8+x2x3x6+x2x3x6x8x9+x2x3x6x7x8+x2x3x5x8+x2x3x5x7+x2x3x5x7x9+x2x3x5x7x8x9+x2x3x5x6+x2x3x5x6x9+x2x3x5x6x7x9+x2x3x4+x2x3x4x8+x2x3x4x7+x2x3x4x7x9+x2x3x4x7x8+x2x3x4x6+x2x3x4x6x9+x2x3x4x6x8x9+x2x3x4x6x7x8+x2x3x4x6x7x8x9+x2x3x4x5x6+x2x3x4x5x6x7x8+x1x8x9+x1x7+x1x7x8+x1x7x8x9+x1x6x7x9+x1x5x9+x1x5x8+x1x5x8x9+x1x5x7+x1x5x7x9+x1x5x7x8x9+x1x5x6+x1x5x6x8+x1x5x6x7+x1x4+x1x4x8+x1x4x8x9+x1x4x7+x1x4x6+x1x4x6x8+x1x4x6x8x9+x1x4x6x7x8+x1x4x6x7x8x9+x1x4x5+x1x4x5x8x9+x1x4x5x7x8+x1x4x5x6x8+x1x4x5x6x7x8x9+x1x3x8+x1x3x8x9+x1x3x7+x1x3x7x8+x1x3x7x8x9+x1x3x6+x1x3x6x8+x1x3x6x8x9+x1x3x6x7x8+x1x3x6x7x8x9+x1x3x5+x1x3x5x9+x1x3x5x7+x1x3x5x7x9+x1x3x5x7x8+x1x3x5x7x8x9+x1x3x5x6+x1x3x5x6x8+x1x3x5x6x8x9+x1x3x5x6x7+x1x3x4x9+x1x3x4x8+x1x3x4x6x8+x1x3x4x5+x1x3x4x5x8x9+x1x3x4x5x7+x1x3x4x5x7x8+x1x3x4x5x7x8x9+x1x3x4x5x6+x1x3x4x5x6x8+x1x3x4x5x6x8x9+x1x3x4x5x6x7+x1x2+x1x2x9+x1x2x7+x1x2x7x9+x1x2x7x8+x1x2x7x8x9+x1x2x6+x1x2x6x9+x1x2x6x8+x1x2x5x9+x1x2x5x8+x1x2x5x6+x1x2x5x6x9+x1x2x5x6x7+x1x2x5x6x7x9+x1x2x5x6x7x8x9+x1x2x4+x1x2x4x7x9+x1x2x4x7x8+x1x2x4x6+x1x2x4x6x9+x1x2x4x6x8+x1x2x4x6x7x8+x1x2x4x5+x1x2x4x5x7+x1x2x4x5x7x9+x1x2x4x5x6x8+x1x2x4x5x6x7x9+x1x2x3x9+x1x2x3x8+x1x2x3x8x9+x1x2x3x7x9+x1x2x3x6x8+x1x2x3x6x7x8x9+x1x2x3x5+x1x2x3x5x9+x1x2x3x5x8+x1x2x3x5x7+x1x2x3x5x7x9+x1x2x3x5x7x8+x1x2x3x5x7x8x9+x1x2x3x5x6x8+x1x2x3x5x6x7x9+x1x2x3x4+x1x2x3x4x8+x1x2x3x4x7x9+x1x2x3x4x7x8x9+x1x2x3x4x6+x1x2x3x4x6x9+x1x2x3x4x6x8+x1x2x3x4x6x7x8+x1x2x3x4x5+x1x2x3x4x5x8x9+x1x2x3x4x5x6x9+x1x2x3x4x5x6x8+x1x2x3x4x5x6x7 ");
  cout<< "The nonlinearity of f2 is "<<f2.nonlinearity()<<endl;
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}
