// This example can be used to test the second-order nonlinearity of any 10-variable Boolean function.
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
  BooleanFunDecoder f(10);
  // You can replace the string here with whatever the ANF of 10-variable function which you want to test.
  f.set_anf("x9+x8+x7+x7x9+x7x9x10+x7x8+x7x8x10+x7x8x9+x6+x6x9x10+x6x7+x6x7x9+x5+x5x9x10+x5x8+x5x7x10+x5x6x10+x5x6x8+x4+x4x9+x4x8+x4x8x10+x4x8x9+x4x7+x4x7x10+x4x7x9+x4x7x8+x4x6+x4x6x10+x4x6x8+x4x6x7+x4x5+x4x5x8+x3+x3x8+x3x8x9+x3x7x10+x3x7x9+x3x7x8+x3x6+x3x6x9+x3x6x8+x3x6x7+x3x5+x3x5x10+x3x5x9+x3x5x8+x3x5x6+x3x4x6+x3x4x5+x2+x2x8x10+x2x8x9+x2x7+x2x7x10+x2x7x9+x2x7x8+x2x6x7+x2x5+x2x5x9+x2x5x6+x2x4+x2x4x8+x2x3x9+x2x3x8+x2x3x6+x2x3x5+x2x3x4+x1+x1x10+x1x9+x1x9x10+x1x8x10+x1x7+x1x7x10+x1x7x9+x1x6x9+x1x5+x1x5x9+x1x5x8+x1x5x7+x1x4+x1x4x10+x1x4x9+x1x4x8+x1x4x7+x1x4x6+x1x4x5+x1x3x10+x1x3x9+x1x3x5+x1x3x4+x1x2x8+x1x2x7+x1x2x4");
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity is "<<f.second_order_nonlinearity_Fourquet_Tavernier()<<endl;

  // Example 2.
  /*
  BooleanFunDecoder f1(10);
  // You can replace the string here with whatever the hexadecimal truth table of 10-variable function which you want to test.
  f1.set_truth_table_hex("C117054D034563F5013F4257590EEE5502061CFC703A475C758631E9FAF94477100B314907F1CEF34C333C88614C65C05F6683581E05F887DEA9DC9771434F4C171131BD1F2752A5224CCE34D2D9ED0F43D13D2F0FC090907A3461C36947D33075DD7B69A02C659335DB3044EC93937CD5F98897D7C0877C5D07703C53CC70C0");
  f1.set_truth_table_done();
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity is "<<f1.second_order_nonlinearity_Fourquet_Tavernier()<<endl;
  */
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}