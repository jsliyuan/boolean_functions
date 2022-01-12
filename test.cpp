#include <iostream>

#include "boolean_fun.h"

using namespace std;

int main() {
  BooleanFun f(6);
  assert(f.var_num() == 6);
  assert(f.value(4, 0,0,0,0) == -1);
  assert(f.value_dec(-1) == -1);
  assert(f.value(6, 0,0,1,1,1,1) == 0);
  assert(f.value_dec(15) == 0);
  assert(f.get_anf() == "0");
  assert(f.get_degree() == 0);
  cout << "End of test for f." << endl;

  BooleanFun g(5, "1");
  assert(g.var_num() == 5);
  assert(g.value(5, 0, 0, 0, 0, 0) == 1);
  assert(g.value_dec(0) == 1);
  assert(g.value(5, 0, 0, 1, 1, 0) == 1);
  assert(g.value_dec(6) == 1);
  assert(g.get_anf() == "1");
  assert(g.get_degree() == 0);
  assert(g.is_equal(f) == false);
  cout << "End of test for g." << endl;

  BooleanFun g2(5, "1+1+0");
  assert(g2.var_num() == 5);
  assert(g2.value(5, 0, 0, 0, 0, 0) == 0);
  assert(g2.value(5, 0, 0, 1, 1, 0) == 0);
  assert(g2.get_anf() == "0");
  assert(g2.get_degree() == 0);
  assert(g2.is_equal(g) == false);
  assert(g2.is_equal(g2) == true);
  cout << "End of test for g2." << endl;

  BooleanFun g3_xor(3, "x1+x2+x3");
  assert(g3_xor.var_num() == 3);
  assert(g3_xor.value(3, 0, 0, 0) == 0);
  assert(g3_xor.value_dec(0) == 0);
  assert(g3_xor.value(3, 1, 1, 0) == 0);
  assert(g3_xor.value(3, 1, 1, 1) == 1);
  assert(g3_xor.value_dec(7) == 1);
  assert(g3_xor.value(3, 0, 0, 1) == 1);
  assert(g3_xor.get_anf() == "x3+x2+x1");
  assert(g3_xor.get_degree() == 1);
  cout << "End of test for g3_xor." << endl;

  BooleanFun g3_and(3, "x1x2x3");
  assert(g3_and.var_num() == 3);
  assert(g3_and.value(3, 0, 0, 0) == 0);
  assert(g3_and.value_dec(0) == 0);
  assert(g3_and.value(3, 1, 1, 0) == 0);
  assert(g3_and.value_dec(6) == 0);
  assert(g3_and.value(3, 1, 1, 1) == 1);
  assert(g3_and.value_dec(7) == 1);
  assert(g3_and.get_anf() == "x1x2x3");
  assert(g3_and.get_degree() == 3);
  cout << "End of test for g3_and." << endl;

  BooleanFun g4(4, "x1+1");
  assert(g4.var_num() == 4);
  assert(g4.value(4, 0, 0, 0, 0) == 1);
  assert(g4.value(4, 1, 0, 1, 0) == 0);
  assert(g4.value(4, 1, 0, 0, 0) == 0);
  assert(g4.value(4, 0, 1, 1, 1) == 1);
  assert(g4.get_anf() == "1+x1");
  assert(g4.get_degree() == 1);
  cout << "End of test for g4." << endl;

  BooleanFun g5(5, "x1x2x3+x4x5");
  assert(g5.var_num() == 5);
  assert(g5.value(5, 1, 1, 1, 0, 1) == 1);
  assert(g5.value(5, 1, 1, 1, 1, 1) == 0);
  assert(g5.value(5, 0, 1, 0, 1, 1) == 1);
  assert(g5.value(5, 0, 0, 0, 0, 1) == 0);
  assert(g5.get_anf() == "x4x5+x1x2x3");
  assert(g5.get_degree() == 3);
  cout << "End of test for g5." << endl;

  BooleanFun g3_and2(3, "1+x1x2x3+1");
  assert(g3_and2.is_equal(g3_and));
  cout << "End of test for g3_and2." << endl;

  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}
