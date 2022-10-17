#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <cassert>

#include "boolean_fun.h"
#include "rotation_sym.h"
#include "permutation.h"

using namespace std;

// s1, s2 are 01 string of the same length
// Return the bitwise xor (as a string).
string string_xor(string s1, string s2) {
  string result = "";
  for (int i = 0; i < s1.length(); i ++) {
    if ((s1[i] == '0' && s2[i] == '1') ||(s1[i] == '1' && s2[i] == '0'))
      result += "1";
    else
      result += "0";
  }
  return result;
}

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
  assert(f.get_coe_list() == "0000000000000000000000000000000000000000000000000000000000000000");
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
  assert(g.get_coe_list() == "10000000000000000000000000000000");
  // Length must be 2^n
  assert(g.set_coe_list("1000000000000000000000000000000") == false);
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
  assert(g3_xor.get_coe_list() == "01101000");
  assert(g3_xor.set_coe_list("01101000"));
  assert(g3_xor.get_anf() == "x3+x2+x1");
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
  cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " sec." << endl;
  cout << "End of high-order nonlinearity test." << endl;

  AffineTrans g7_1(6, "[010000 001000 000100 000010 000001 110000]010000");
  fn67.apply_affine_trans(g7_1);
  fn67.trim_degree_below(4);
  assert(fn67.get_anf() == "x2x4x5x6+x2x3x4x5x6+x1x2x4x5x6+x1x2x3x4x5x6");

  BooleanFun fn67_af_copy(fn67);
  assert(fn67_af_copy.get_anf() == "x2x4x5x6+x2x3x4x5x6+x1x2x4x5x6+x1x2x3x4x5x6");
  BooleanFun fn61_copy = fn61;
  assert(fn61_copy.get_anf() == "x1x2x3x4");
  cout << "End of copy constructor test." << endl;

  fn67_af_copy = fn62;
  assert(fn67_af_copy.get_anf() == fn62.get_anf());
  fn67_af_copy = xor3;
  assert(fn67_af_copy.get_anf() == "x3+x2+x1");
  assert(fn67_af_copy.var_num() == 3);
  cout << "End of assignment constructor test." << endl;

  BooleanFun fn6a(6, "x1x2x6+x1x2x5");
  assert(fn6a.get_coe_list() == "0000000000000000000000000000000000000000000000000110000000000000");
  fn6a.set_coe_list(fn6a.get_coe_list());
  assert(fn6a.get_anf() == "x1x2x6+x1x2x5");
  BooleanFun fn6b(6, "x2x3x6+x1x5x6+x1x4x6+x1x3x5+x1x2x5+x1x2x4");
  assert(fn6b.get_coe_list() == "0000000000000000000000000100000000010100001000000010100000000000");
  fn6b.set_coe_list(fn6b.get_coe_list());
  assert(fn6b.get_anf() == "x2x3x6+x1x5x6+x1x4x6+x1x3x5+x1x2x5+x1x2x4");
  BooleanFun fn6apb = fn6a;
  fn6apb.add(fn6b);
  assert(fn6apb.get_anf() == "x2x3x6+x1x5x6+x1x4x6+x1x3x5+x1x2x6+x1x2x4");
  assert(fn6apb.get_coe_list() == string_xor(fn6a.get_coe_list(), fn6b.get_coe_list()));
  cout << "End of get_coe_list and set_coe_list test." << endl;

  BooleanFun fn6_rand(6);
  fn6_rand.set_truth_table_random();
  cout << "Generate a random 6-variable Boolean function" << endl;
  cout << fn6_rand.get_anf() << endl;
  cout << "End of set_truth_table_random test." << endl;

  BooleanFun f9a(9);
  f9a.set_truth_table_hex("125425D30A398F36508C06817BEE122E250D973314F976AED58A3EA9120DA4FE0E4D4575C42DD0426365EBA7FC5F45BE9B2F336981B5E1863618F49474F6FE00");
  f9a.set_truth_table_done();
  assert(f9a.var_num() == 9);
  cout<<f9a.get_anf()<<endl;
  assert(f9a.nonlinearity() == 242);
  BooleanFun sub0_f9a = f9a.sub_function(0);
  assert(sub0_f9a.var_num() == 8);
  //cout<<sub0_f9a.get_anf()<<endl;
  //cout<<sub0_f9a.nonlinearity()<<endl;
  BooleanFun sub1_f9a = f9a.sub_function(1);
  //cout<<sub1_f9a.get_anf()<<endl;
  //cout<<sub1_f9a.nonlinearity()<<endl;
  cout << "End of test for sub_function() for f9a." << endl;
  
  BooleanFun f9b(9);
  f9b.set_truth_table_hex("68B7EF2DA03B0D3EA00DB6A96DD99AEAFDB9C842B6D5DC8C4526CE0DD29020DBB75FE3314568344E73688FF0CB2482E065231869E1AA4583765CC491F8A8DB12");
  f9b.set_truth_table_done();
  assert(f9b.var_num() == 9);
  cout<<f9b.get_anf()<<endl;
  assert(f9b.nonlinearity() == 242);
  BooleanFun sub0_f9b = f9b.sub_function(0);
  assert(sub0_f9b.var_num() == 8);
  cout<<sub0_f9b.get_anf()<<endl;
  cout<<sub0_f9b.nonlinearity()<<endl;
  BooleanFun sub1_f9b = f9b.sub_function(1);
  cout<<sub1_f9b.get_anf()<<endl;
  cout<<sub1_f9b.nonlinearity()<<endl;
  cout << "End of test for sub_function() for f9b." << endl;

  BooleanFun f9c(9);
  f9c.set_truth_table_hex("3740B6A118A1E19642A85E2B7E2F3C3CB65FA0D95EC9DB1EA92BDB3666185AE0087F5FE6E0757106A12FC918754C40E8A1BCCB7A714032A8961456E066E8A801");
  f9c.set_truth_table_done();
  assert(f9c.var_num() == 9);
  cout<<f9c.get_anf()<<endl;
  assert(f9c.nonlinearity() == 242);
  BooleanFun sub0_f9c = f9c.sub_function(0);
  assert(sub0_f9c.var_num() == 8);
  //cout<<sub0_f9c.get_anf()<<endl;
  //cout<<sub0_f9c.nonlinearity()<<endl;
  BooleanFun sub1_f9c = f9c.sub_function(1);
  //cout<<sub1_f9c.get_anf()<<endl;
  //cout<<sub1_f9c.nonlinearity()<<endl;
  cout << "End of test for sub_function() for f9c." << endl;
  
  BooleanFun f9d(9);
  f9d.set_truth_table_hex("7B8F94BAD364DAC9931906F9465FF33E921E13D7552DAFD684757B662FDA3C68FA8D94B3C3659B5FCC46FD1518050F97A1E02039AAF74337134F30AB5B41D9DE");
  f9d.set_truth_table_done();
  assert(f9d.var_num() == 9);
  cout<<f9d.get_anf()<<endl;
  assert(f9d.nonlinearity() == 242);
  BooleanFun sub0_f9d = f9d.sub_function(0);
  assert(sub0_f9d.var_num() == 8);
  //cout<<sub0_f9d.get_anf()<<endl;
  //cout<<sub0_f9d.nonlinearity()<<endl;
  BooleanFun sub1_f9d = f9d.sub_function(1);
  //cout<<sub1_f9d.get_anf()<<endl;
  //cout<<sub1_f9d.nonlinearity()<<endl;
  cout << "End of test for sub_function() for f9d." << endl;

  BooleanFun f9e(9);
  f9e.set_truth_table_hex("0331786B34D878855663A2E961F1CB4F779EBBF6881ABB24AC033E6C2B32E0493D0891DB1888EA5E6F910310311532FC68D5F2A4B5BE6445E41F64299F0CC99A");
  f9e.set_truth_table_done();
  assert(f9e.var_num() == 9);
  cout<<f9e.get_anf()<<endl;
  assert(f9e.nonlinearity() == 242);
  BooleanFun sub0_f9e = f9e.sub_function(0);
  assert(sub0_f9e.var_num() == 8);
  //cout<<sub0_f9e.get_anf()<<endl;
  //cout<<sub0_f9e.nonlinearity()<<endl;
  BooleanFun sub1_f9e = f9e.sub_function(1);
  //cout<<sub1_f9e.get_anf()<<endl;
  //cout<<sub1_f9e.nonlinearity()<<endl;
  cout << "End of test for sub_function() for f9e." << endl;
  
  BooleanFun rsym(3);
  RotationSym r(3);
  rsym.set_random_sym(r.get_all_orbits());
  cout<< " The ANF of rsym is "<<rsym.get_anf()<<endl;
  cout<< " The degree of rsym is "<<rsym.get_degree()<<endl;
  
  BooleanFun rsym1(4);
  RotationSym r_4(4);
  rsym1.set_random_sym(r_4.get_all_orbits());
  cout<< "The ANF of rsym1 is "<<rsym1.get_anf()<<endl;
  cout<< "The degree of rsym1 is "<<rsym1.get_degree()<<endl;
  
  BooleanFun rsym2(4,"0");
  RotationSym r_4_1(4);
  assert(rsym2.get_anf()=="0");
  rsym2.set_truth_table_orbit(r_4_1.get_full_orbit(0), 1);
  rsym2.set_truth_table_done();
  assert(rsym2.get_anf()=="1+x4+x3+x3x4+x2+x2x4+x2x3+x2x3x4+x1+x1x4+x1x3+x1x3x4+x1x2+x1x2x4+x1x2x3+x1x2x3x4");
  assert(rsym2.get_degree()==4);
  rsym2.set_truth_table_orbit(r_4_1.get_full_orbit(2), 1);
  rsym2.set_truth_table_done();
  assert(rsym2.get_anf()=="1+x4+x3+x2+x2x4+x2x3x4+x1+x1x3+x1x3x4+x1x2x4+x1x2x3+x1x2x3x4");
  assert(rsym2.get_degree()==4);
  rsym2.set_truth_table_orbit(r_4_1.get_full_orbit(1), 1);
  rsym2.set_truth_table_done();
  assert(rsym2.get_anf()=="1+x2x4+x1x3+x1x2x3x4");
  assert(rsym2.get_degree()==4);
  rsym2.set_truth_table_orbit(r_4_1.get_full_orbit(2), 0);
  rsym2.set_truth_table_done();
  rsym2.set_truth_table_orbit(r_4_1.get_full_orbit(0), 0);
  rsym2.set_truth_table_done();
  rsym2.set_truth_table_orbit(r_4_1.get_full_orbit(1), 0);
  rsym2.set_truth_table_done();
  assert(rsym2.get_anf()=="0");
  assert(rsym2.get_degree()==0);
  
  // TODO(yl): g++ version does not support {} initialization
  // vector<int> din{3,5,6,9,10,12};
  vector <int> din;
  din.push_back(3);
  din.push_back(5);
  din.push_back(6);
  din.push_back(9);
  din.push_back(10);
  din.push_back(12);
  rsym2.set_truth_table_orbit(din, 1);
  rsym2.set_truth_table_done();
  assert(rsym2.get_anf()=="x3x4+x2x4+x2x3+x2x3x4+x1x4+x1x3+x1x3x4+x1x2+x1x2x4+x1x2x3");
  assert(rsym2.get_degree()==3);
  
  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}
