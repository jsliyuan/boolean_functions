#include <iostream>
#include <time.h>
#include <set>

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
  assert(f.is_homogenous() == true);
  assert(f.walsh_transform(0) == (1<<6));
  assert(f.nonlinearity() == 0);
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
  assert(g.dist(f) == -1);
  assert(g.is_homogenous() == true);
  assert(g.walsh_transform(0) == -(1<<5));
  assert(g.nonlinearity() == 0);
  cout << "End of test for g." << endl;

  BooleanFun g2(5, "1+1+0");
  assert(g2.var_num() == 5);
  assert(g2.value(5, 0, 0, 0, 0, 0) == 0);
  assert(g2.value(5, 0, 0, 1, 1, 0) == 0);
  assert(g2.get_anf() == "0");
  assert(g2.get_degree() == 0);
  assert(g2.is_equal(g) == false);
  assert(g2.is_equal(g2) == true);
  assert(g2.dist(g) == (1<<5));
  BooleanFun g2_same(5, "0");
  assert(g2_same == g2);
  assert(g2 < g);
  set<BooleanFun> bf_set;
  BooleanFun *bf_temp = new BooleanFun(5, "0");
  bf_set.insert(*bf_temp);
  bf_temp = new BooleanFun(5, "1");
  bf_set.insert(*bf_temp);
  bf_temp = new BooleanFun(5, "1+1");
  bf_set.insert(*bf_temp);
  assert(bf_set.size() == 2);
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
  assert(g3_xor.is_homogenous() == true);
  assert(g3_xor.walsh_transform(0) == 0);
  assert(g3_xor.walsh_transform(7) == 8);
  assert(g3_xor.nonlinearity() == 0);
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
  assert(g3_and.dist(g3_xor) == 3);
  assert(g3_and.walsh_transform(0) == 6);
  assert(g3_and.walsh_transform(4) == 2);
  assert(g3_and.nonlinearity() == 1);
  assert(g3_and.nonlinearity(2) == 1);
  BooleanFun g3_and_sub0 = g3_and.sub_function(0);
  assert(g3_and_sub0.get_anf() == "0");
  BooleanFun g3_and_sub1 = g3_and.sub_function(1);
  assert(g3_and_sub1.get_anf() == "x1x2");
  cout << "End of test for g3_and." << endl;

  BooleanFun g4(4, "x1+1");
  assert(g4.var_num() == 4);
  assert(g4.value(4, 0, 0, 0, 0) == 1);
  assert(g4.value(4, 1, 0, 1, 0) == 0);
  assert(g4.value(4, 1, 0, 0, 0) == 0);
  assert(g4.value(4, 0, 1, 1, 1) == 1);
  assert(g4.get_anf() == "1+x1");
  assert(g4.get_degree() == 1);
  assert(g4.is_homogenous() == false);
  assert(g4.nonlinearity() == 0);
  cout << "End of test for g4." << endl;

  // Check if the extra spaces are filtered.
  BooleanFun g5(5, "x1x2x3 + x4x5");
  assert(g5.var_num() == 5);
  assert(g5.value(5, 1, 1, 1, 0, 1) == 1);
  assert(g5.value(5, 1, 1, 1, 1, 1) == 0);
  assert(g5.value(5, 0, 1, 0, 1, 1) == 1);
  assert(g5.value(5, 0, 0, 0, 0, 1) == 0);
  assert(g5.get_anf() == "x4x5+x1x2x3");
  assert(g5.get_degree() == 3);
  assert(g5.nonlinearity() == 10);
  cout << "End of test for g5." << endl;

  BooleanFun g3_and2(3, "1+x1x2x3+1");
  assert(g3_and2.is_equal(g3_and));
  cout << "End of test for g3_and2." << endl;

  // Be careful. g3_and is changed!
  assert(g3_and.add(g3_xor) == true);
  assert(g3_and.get_anf() == "x3+x2+x1+x1x2x3");
  cout << "End of test for g3_and + g3_xor" << endl;

  BooleanFun g3_zero(3, "0");
  // Be careful, g3_and is set to zero.
  assert(g3_and.add(g3_and) == true);
  assert(g3_and.is_equal(g3_zero));
  cout << "End of test for g3_and + g3_and = 0" << endl;

  assert(g3_and.add(g5) == false);
  cout << "End of test for g3_and + g5" << endl;

  BooleanFun g3_one(3, "1");
  assert(g3_and2.mult(g5) == false);
  assert(g3_and2.mult(g3_one) == true);
  assert(g3_and2.get_anf() == "x1x2x3");
  // (x1+x2+x3)*x1x2x3 = x1x2x3
  assert(g3_and2.mult(g3_xor) == true);
  assert(g3_and2.get_anf() == "x1x2x3");

  BooleanFun g5_d2(5, "x1x2+x3x5");
  // (x1x2 + x3x5) * (x1x2x3+x4x5)
  // = x1x2x3 + x1x2x4x5 + x1x2x3x5 + x3x4x5
  assert(g5_d2.mult(g5) == true);
  assert(g5_d2.get_anf() == "x3x4x5+x1x2x4x5+x1x2x3+x1x2x3x5");
  assert(g5_d2.get_degree() == 4);
  cout << "End of test for mult()" << endl;

  g3_one.negate();
  assert(g3_one.get_anf() == "0");
  g3_one.negate();
  assert(g3_one.get_anf() == "1");
  cout << "End of test for negate()" << endl;
  g3_xor.negate();
  assert(g3_xor.get_anf() == "1+x3+x2+x1");
  g3_xor.negate();
  assert(g3_xor.get_anf() == "x3+x2+x1");

  AffineTrans trans3(3);
  trans3.set_a(1, 1, 1);
  trans3.set_a(1, 2, 1);
  trans3.set_a(2, 2, 1);
  trans3.set_a(2, 3, 1);
  trans3.set_a(3, 3, 1);
  g3_xor.apply_affine_trans(trans3);
  assert(g3_xor.get_anf() == "x1");

  BooleanFun g3_and3(3, "x1x2x3");
  // (x1+x2)*(x2+x3)*x3 = x1x2x3 + x1x3
  g3_and3.apply_affine_trans(trans3);
  assert(g3_and3.get_anf() == "x1x3+x1x2x3");
  assert(g3_and3.is_homogenous() == false);
  assert(g3_and3.set_anf("x1x2x3"));
  assert(g3_and3.get_anf() == "x1x2x3");
  assert(g3_and3.is_homogenous() == true);
  assert(g3_and3.value(3, 1, 0, 0) == 0);
  assert(g3_and3.value(3, 1, 1, 1) == 1);
  cout << "End of test for apply_affine_trans()" << endl;

  BooleanFun g5_mixed(5, "x1x2x3x4x5+x1x2x4x5+x3x4+x5+x1");
  g5_mixed.trim_degree_below(5);
  assert(g5_mixed.get_anf() == "x1x2x3x4x5");
  assert(g5_mixed.value(5, 1, 1, 1, 1, 1) == 1);
  assert(g5_mixed.value(5, 1, 1, 0, 1, 1) == 0);
  assert(g5_mixed.value(5, 1, 0, 0, 0, 0) == 0);

  g5_mixed.set_anf("x1x2x3x4x5+1");
  g5_mixed.trim_degree_below(1);
  assert(g5_mixed.get_anf() == "x1x2x3x4x5");
  g5_mixed.trim_degree_below(6);
  assert(g5_mixed.get_anf() == "0");
  cout << "End of test for trim_degree_below()" << endl;

  BooleanFun g6_bent(6, "x1x2+x3x4+x5x6");
  assert(g6_bent.nonlinearity() == 28);
  cout << "End of test for nonlinearity() for 6-variable bent function" << endl;

  BooleanFun g4_bent(4, "x1x2+x3x4");
  assert(g4_bent.nonlinearity() == 6);
  cout << "End of test for nonlinearity() for 4-variable bent function" << endl;

  BooleanFun delta4(4);
  assert(delta4.get_anf() == "0");
  assert(delta4.set_truth_table(15, 1));
  delta4.set_truth_table_done();
  assert(delta4.get_anf() == "x1x2x3x4");
  assert(delta4.set_truth_table(15, 0));
  assert(delta4.set_truth_table(14, 1));
  delta4.set_truth_table_done();
  assert(delta4.get_anf() == "x1x2x3+x1x2x3x4");
  cout << "End of test for set_truth_table() for delta4." << endl;

  BooleanFun xor3(3);
  assert(xor3.get_anf() == "0");
  assert(xor3.set_truth_table(1, 1));
  assert(xor3.set_truth_table(2, 1));
  assert(xor3.set_truth_table(4, 1));
  assert(xor3.set_truth_table(7, 1));
  xor3.set_truth_table_done();
  assert(xor3.get_anf() == "x3+x2+x1");
  xor3.set_anf_coe(0, 1);
  xor3.set_anf_coe(1, 0);
  xor3.set_anf_coe_done();
  assert(xor3.get_anf() == "1+x2+x1");
  assert(xor3.value(3, 0, 1, 1) == 0);
  assert(xor3.value(3, 0, 0, 0) == 1);
  cout << "End of test for set_truth_table() for xor3." << endl;

  assert(xor3.set_anf("x3+x2+x1"));
  BooleanFun sub0 = xor3.sub_function(0);
  assert(sub0.var_num() == 2);
  assert(sub0.get_anf() == "x2+x1");
  BooleanFun sub1 = xor3.sub_function(1);
  assert(sub1.var_num() == 2);
  assert(sub1.get_anf() == "1+x2+x1");
  cout << "End of test for sub_function() for xor3." << endl;

  /*
  cout << "Computing nl3 for some 7-variable function... (slow)" << endl;
  BooleanFun fn71(7, "x1x2x3x4+x1x4x6x7+x2x3x6x7+x3x4x5x7");
  assert(fn71.nonlinearity(3) == 20);
  cout << "End of nl3 for some 7-variable function." << endl;
  */

  cout << "Running high-order nonlinearity test... (slow)" << endl;
  // Start the clock
  clock_t tStart = clock();
  BooleanFun fn61(6, "x1x2x3x4");
  assert(fn61.nonlinearity(3) == 4);
  BooleanFun fn62(6, "x1x2x4x5+x1x2x3x6");
  assert(fn62.nonlinearity(3) == 6);
  BooleanFun fn63(6, "x2x3x4x5+x1x3x4x6+x1x2x5x6");
  assert(fn63.nonlinearity(3) == 8);
  BooleanFun fn64(6, "x1x2x3x4x5");
  assert(fn64.nonlinearity(3) == 2);
  BooleanFun fn65(6, "x1x2x3x4x5+x1x2x3x6");
  assert(fn65.nonlinearity(3) == 4);
  BooleanFun fn66(6, "x1x2x3x4x5+x1x3x4x6+x1x2x5x6");
  assert(fn66.nonlinearity(3) == 6);
  BooleanFun fn67(6, "x1x2x3x4x5x6");
  assert(fn67.nonlinearity(3) == 1);
  BooleanFun fn68(6, "x1x2x3x4x5x6+x1x2x3x4");
  assert(fn68.nonlinearity(3) == 3);
  BooleanFun fn69(6, "x1x2x3x4x5x6+x1x2x4x5+x1x2x3x6");
  assert(fn69.nonlinearity(3) == 5);
  BooleanFun fn610(6, "x1x2x3x4x5x6+x2x3x4x5+x1x3x4x6+x1x2x5x6");
  assert(fn610.nonlinearity(3) == 7);
  cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " sec.";
  cout << "End of high-order nonlinearity test." << endl;

  AffineTrans g7_1(6, "[010000 001000 000100 000010 000001 110000]010000");
  fn67.apply_affine_trans(g7_1);
  fn67.trim_degree_below(4);
  assert(fn67.get_anf() == "x2x4x5x6+x2x3x4x5x6+x1x2x4x5x6+x1x2x3x4x5x6");

  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}
