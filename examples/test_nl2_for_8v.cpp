// This example can be used to test the second-order nonlinearity of any 8-variable Boolean function.
// It is so easy to verify the result.

#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <cassert>
#include <vector>

#include "../boolean_fun.h"
#include "../boolean_fun_decoder.h"
#include "../homogenous_bf_generator.h"

using namespace std;

int main() {
  // Example 1. This example is from the classification of RM(3,8)/RM(2,8) in "GL(m,2) Acting on R(r,m)/R(r- 1,m)" by Xiang-dong Hou.
  // The 8-variable Boolean function has second-order nonlinearity 88.

  // It is the first time that the 8-variable Boolean function with second-nonlinearity 88 was found,
  // and we double check that it is true.

  BooleanFunDecoder f(8);
  // You can replace the string here with whatever the ANF of 8-variable function which you want to test.
  f.set_anf("x1x2x3+x4x5x6+x1x4x7+x2x5x7+x1x6x8+x1x7x8+x2x4x8+x3x5x8");
  cout<<"The second-order nonlinearity of f is "<<f.second_order_nonlinearity_Fourquet_Tavernier()<<endl;


  // Example 2. The example is obtained by our experiment.
  // We check this 8-variable Boolean function in the hexadecimal truth table has second-order nonlinearity 88.

  BooleanFunDecoder f1(8);
  // You can replace the string here with whatever the hexadecimal truth table of 8-variable function which you want to test.
  f1.set_truth_table_hex("964841A34106991D4205037895B424C6601B1255213C5C8287659C423942D26A");
  f1.set_truth_table_done();
  BooleanFun sub1(7);
  sub1=f1.sub_function(0);
  cout<<sub1.nonlinearity(2)<<endl;
  int max_val=0;
  HomogenousBfGenerator gen(7,2);
  while(gen.next()){
    BooleanFun g(7);
    g=*gen.get_boolean_fun();
    g.add(sub1);
    if(g.nonlinearity()>max_val){
      max_val=g.nonlinearity();
    }
  }
  cout<<"the max of sub1 is "<<max_val<<endl;
  
  // call second_order_nonlinearity_Fourquet_Tavernier() to compute second-order nonlinearity
  cout<<"The second-order nonlinearity of f1 is "<<f1.second_order_nonlinearity_Fourquet_Tavernier()<<endl;
  
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}