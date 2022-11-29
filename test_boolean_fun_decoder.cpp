#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>

#include "boolean_fun.h"
#include "boolean_fun_decoder.h"
#include "rotation_sym.h"
#include "permutation.h"
#include "perm_group.h"
using namespace std;

bool vector_of_bfs_contasins_anf(string anf, vector<BooleanFun> term){
  vector<string> term1;
  for(int i=0;i<term.size();i++){
    term1.push_back((term.at(i)).get_anf());
  }
  if(std::find(term1.begin(), term1.end(), anf) != term1.end()){
    return true ;
  }
  else{
    return false;
  }
}

bool float_equals(double val,double target) {
  const double EPS=1e-8;
  if(val>=target-EPS && val<target+EPS) {
    return true;
  } else {
    return false;
  }
}
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
  BooleanFunDecoder f(6);
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

  BooleanFunDecoder g(5, "1");
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

  BooleanFunDecoder g2(5, "1+1+0");
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
  set<BooleanFunDecoder> bf_set;
  BooleanFunDecoder *bf_temp = new BooleanFunDecoder(5, "0");
  bf_set.insert(*bf_temp);
  bf_temp = new BooleanFunDecoder(5, "1");
  bf_set.insert(*bf_temp);
  bf_temp = new BooleanFunDecoder(5, "1+1");
  bf_set.insert(*bf_temp);
  assert(bf_set.size() == 2);
  cout << "End of test for g2." << endl;

  BooleanFunDecoder g3_xor(3, "x1+x2+x3");
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

  BooleanFunDecoder g3_and(3, "x1x2x3");
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

  BooleanFunDecoder g4(4, "x1+1");
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
  BooleanFunDecoder g5(5, "x1x2x3 + x4x5");
  assert(g5.var_num() == 5);
  assert(g5.value(5, 1, 1, 1, 0, 1) == 1);
  assert(g5.value(5, 1, 1, 1, 1, 1) == 0);
  assert(g5.value(5, 0, 1, 0, 1, 1) == 1);
  assert(g5.value(5, 0, 0, 0, 0, 1) == 0);
  assert(g5.get_anf() == "x4x5+x1x2x3");
  assert(g5.get_degree() == 3);
  assert(g5.nonlinearity() == 10);
  cout << "End of test for g5." << endl;

  BooleanFunDecoder g3_and2(3, "1+x1x2x3+1");
  assert(g3_and2.is_equal(g3_and));
  cout << "End of test for g3_and2." << endl;

  // Be careful. g3_and is changed!
  assert(g3_and.add(g3_xor) == true);
  assert(g3_and.get_anf() == "x3+x2+x1+x1x2x3");
  cout << "End of test for g3_and + g3_xor" << endl;

  BooleanFunDecoder g3_zero(3, "0");
  // Be careful, g3_and is set to zero.
  assert(g3_and.add(g3_and) == true);
  assert(g3_and.is_equal(g3_zero));
  cout << "End of test for g3_and + g3_and = 0" << endl;

  assert(g3_and.add(g5) == false);
  cout << "End of test for g3_and + g5" << endl;

  BooleanFunDecoder g3_one(3, "1");
  assert(g3_and2.mult(g5) == false);
  assert(g3_and2.mult(g3_one) == true);
  assert(g3_and2.get_anf() == "x1x2x3");
  // (x1+x2+x3)*x1x2x3 = x1x2x3
  assert(g3_and2.mult(g3_xor) == true);
  assert(g3_and2.get_anf() == "x1x2x3");

  BooleanFunDecoder g5_d2(5, "x1x2+x3x5");
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

  BooleanFunDecoder g3_and3(3, "x1x2x3");
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

  BooleanFunDecoder g5_mixed(5, "x1x2x3x4x5+x1x2x4x5+x3x4+x5+x1");
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

  BooleanFunDecoder g6_bent(6, "x1x2+x3x4+x5x6");
  assert(g6_bent.nonlinearity() == 28);
  cout << "End of test for nonlinearity() for 6-variable bent function" << endl;

  BooleanFunDecoder g4_bent(4, "x1x2+x3x4");
  assert(g4_bent.nonlinearity() == 6);
  cout << "End of test for nonlinearity() for 4-variable bent function" << endl;

  BooleanFunDecoder delta4(4);
  assert(delta4.get_anf() == "0");
  assert(delta4.set_truth_table(15, 1));
  delta4.set_truth_table_done();
  assert(delta4.get_anf() == "x1x2x3x4");
  assert(delta4.set_truth_table(15, 0));
  assert(delta4.set_truth_table(14, 1));
  delta4.set_truth_table_done();
  assert(delta4.get_anf() == "x1x2x3+x1x2x3x4");
  cout << "End of test for set_truth_table() for delta4." << endl;

  BooleanFunDecoder xor3(3);
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
  BooleanFunDecoder fn61(6, "x1x2x3x4");
  assert(fn61.nonlinearity(3) == 4);
  BooleanFunDecoder fn62(6, "x1x2x4x5+x1x2x3x6");
  assert(fn62.nonlinearity(3) == 6);
  BooleanFunDecoder fn63(6, "x2x3x4x5+x1x3x4x6+x1x2x5x6");
  assert(fn63.nonlinearity(3) == 8);
  BooleanFunDecoder fn64(6, "x1x2x3x4x5");
  assert(fn64.nonlinearity(3) == 2);
  BooleanFunDecoder fn65(6, "x1x2x3x4x5+x1x2x3x6");
  assert(fn65.nonlinearity(3) == 4);
  BooleanFunDecoder fn66(6, "x1x2x3x4x5+x1x3x4x6+x1x2x5x6");
  assert(fn66.nonlinearity(3) == 6);
  BooleanFunDecoder fn67(6, "x1x2x3x4x5x6");
  assert(fn67.nonlinearity(3) == 1);
  BooleanFunDecoder fn68(6, "x1x2x3x4x5x6+x1x2x3x4");
  assert(fn68.nonlinearity(3) == 3);
  BooleanFunDecoder fn69(6, "x1x2x3x4x5x6+x1x2x4x5+x1x2x3x6");
  assert(fn69.nonlinearity(3) == 5);
  BooleanFunDecoder fn610(6, "x1x2x3x4x5x6+x2x3x4x5+x1x3x4x6+x1x2x5x6");
  assert(fn610.nonlinearity(3) == 7);
  cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " sec." << endl;
  cout << "End of high-order nonlinearity test." << endl;

  AffineTrans g7_1(6, "[010000 001000 000100 000010 000001 110000]010000");
  fn67.apply_affine_trans(g7_1);
  fn67.trim_degree_below(4);
  assert(fn67.get_anf() == "x2x4x5x6+x2x3x4x5x6+x1x2x4x5x6+x1x2x3x4x5x6");

  BooleanFunDecoder fn67_af_copy(fn67);
  assert(fn67_af_copy.get_anf() == "x2x4x5x6+x2x3x4x5x6+x1x2x4x5x6+x1x2x3x4x5x6");
  BooleanFunDecoder fn61_copy = fn61;
  assert(fn61_copy.get_anf() == "x1x2x3x4");
  cout << "End of copy constructor test." << endl;

  fn67_af_copy = fn62;
  assert(fn67_af_copy.get_anf() == fn62.get_anf());
  fn67_af_copy = xor3;
  assert(fn67_af_copy.get_anf() == "x3+x2+x1");
  assert(fn67_af_copy.var_num() == 3);
  cout << "End of assignment constructor test." << endl;

  BooleanFunDecoder fn6a(6, "x1x2x6+x1x2x5");
  assert(fn6a.get_coe_list() == "0000000000000000000000000000000000000000000000000110000000000000");
  fn6a.set_coe_list(fn6a.get_coe_list());
  assert(fn6a.get_anf() == "x1x2x6+x1x2x5");
  BooleanFunDecoder fn6b(6, "x2x3x6+x1x5x6+x1x4x6+x1x3x5+x1x2x5+x1x2x4");
  assert(fn6b.get_coe_list() == "0000000000000000000000000100000000010100001000000010100000000000");
  fn6b.set_coe_list(fn6b.get_coe_list());
  assert(fn6b.get_anf() == "x2x3x6+x1x5x6+x1x4x6+x1x3x5+x1x2x5+x1x2x4");
  BooleanFunDecoder fn6apb = fn6a;
  fn6apb.add(fn6b);
  assert(fn6apb.get_anf() == "x2x3x6+x1x5x6+x1x4x6+x1x3x5+x1x2x6+x1x2x4");
  assert(fn6apb.get_coe_list() == string_xor(fn6a.get_coe_list(), fn6b.get_coe_list()));
  cout << "End of get_coe_list and set_coe_list test." << endl;

  BooleanFunDecoder fn6_rand(6);
  fn6_rand.set_truth_table_random();
  cout << "Generate a random 6-variable Boolean function" << endl;
  cout << fn6_rand.get_anf() << endl;
  cout << "End of set_truth_table_random test." << endl;

  BooleanFunDecoder f9a(9);
  f9a.set_truth_table_hex("125425D30A398F36508C06817BEE122E250D973314F976AED58A3EA9120DA4FE0E4D4575C42DD0426365EBA7FC5F45BE9B2F336981B5E1863618F49474F6FE00");
  f9a.set_truth_table_done();
  assert(f9a.var_num() == 9);
  // cout<<f9a.get_anf()<<endl;
  assert(f9a.nonlinearity() == 242);
  BooleanFun sub0_f9a = f9a.sub_function(0);
  assert(sub0_f9a.var_num() == 8);
  // cout<<sub0_f9a.get_anf()<<endl;
  assert(sub0_f9a.nonlinearity() == 114);
  BooleanFun sub1_f9a = f9a.sub_function(1);
  // cout<<sub1_f9a.get_anf()<<endl;
  assert(sub1_f9a.nonlinearity() == 114);
  cout << "End of test for sub_function() for f9a." << endl;
  
  BooleanFunDecoder f9b(9);
  f9b.set_truth_table_hex("68B7EF2DA03B0D3EA00DB6A96DD99AEAFDB9C842B6D5DC8C4526CE0DD29020DBB75FE3314568344E73688FF0CB2482E065231869E1AA4583765CC491F8A8DB12");
  f9b.set_truth_table_done();
  assert(f9b.var_num() == 9);
  // cout<<f9b.get_anf()<<endl;
  assert(f9b.nonlinearity() == 242);
  BooleanFun sub0_f9b = f9b.sub_function(0);
  assert(sub0_f9b.var_num() == 8);
  //cout<<sub0_f9b.get_anf()<<endl;
  assert(sub0_f9b.nonlinearity() == 114);
  BooleanFun sub1_f9b = f9b.sub_function(1);
  //cout<<sub1_f9b.get_anf()<<endl;
  assert(sub1_f9b.nonlinearity() == 114);
  cout << "End of test for sub_function() for f9b." << endl;

  BooleanFunDecoder f9c(9);
  f9c.set_truth_table_hex("3740B6A118A1E19642A85E2B7E2F3C3CB65FA0D95EC9DB1EA92BDB3666185AE0087F5FE6E0757106A12FC918754C40E8A1BCCB7A714032A8961456E066E8A801");
  f9c.set_truth_table_done();
  assert(f9c.var_num() == 9);
  // cout<<f9c.get_anf()<<endl;
  assert(f9c.nonlinearity() == 242);
  BooleanFun sub0_f9c = f9c.sub_function(0);
  assert(sub0_f9c.var_num() == 8);
  // cout<<sub0_f9c.get_anf()<<endl;
  assert(sub0_f9c.nonlinearity() == 114);
  BooleanFun sub1_f9c = f9c.sub_function(1);
  // cout<<sub1_f9c.get_anf()<<endl;
  assert(sub1_f9c.nonlinearity() == 114);
  cout << "End of test for sub_function() for f9c." << endl;
  
  BooleanFunDecoder f9d(9);
  f9d.set_truth_table_hex("7B8F94BAD364DAC9931906F9465FF33E921E13D7552DAFD684757B662FDA3C68FA8D94B3C3659B5FCC46FD1518050F97A1E02039AAF74337134F30AB5B41D9DE");
  f9d.set_truth_table_done();
  assert(f9d.var_num() == 9);
  // cout<<f9d.get_anf()<<endl;
  assert(f9d.nonlinearity() == 242);
  BooleanFun sub0_f9d = f9d.sub_function(0);
  assert(sub0_f9d.var_num() == 8);
  // cout<<sub0_f9d.get_anf()<<endl;
  assert(sub0_f9d.nonlinearity() == 114);
  BooleanFun sub1_f9d = f9d.sub_function(1);
  // cout<<sub1_f9d.get_anf()<<endl;
  assert(sub1_f9d.nonlinearity() == 114);
  cout << "End of test for sub_function() for f9d." << endl;

  BooleanFunDecoder f9e(9);
  f9e.set_truth_table_hex("0331786B34D878855663A2E961F1CB4F779EBBF6881ABB24AC033E6C2B32E0493D0891DB1888EA5E6F910310311532FC68D5F2A4B5BE6445E41F64299F0CC99A");
  f9e.set_truth_table_done();
  assert(f9e.var_num() == 9);
  // cout<<f9e.get_anf()<<endl;
  assert(f9e.nonlinearity() == 242);
  BooleanFun sub0_f9e = f9e.sub_function(0);
  assert(sub0_f9e.var_num() == 8);
  // cout<<sub0_f9e.get_anf()<<endl;
  assert(sub0_f9e.nonlinearity() == 114);
  BooleanFun sub1_f9e = f9e.sub_function(1);
  // cout<<sub1_f9e.get_anf()<<endl;
  assert(sub1_f9e.nonlinearity() == 114);
  cout << "End of test for sub_function() for f9e." << endl;
  
  BooleanFunDecoder rsym(3);
  RotationSym r(3);
  rsym.set_random_sym(r.get_all_orbits());
  cout<< " The ANF of rsym is "<<rsym.get_anf()<<endl;
  cout<< " The degree of rsym is "<<rsym.get_degree()<<endl;
  
  BooleanFunDecoder rsym1(4);
  RotationSym r_4(4);
  rsym1.set_random_sym(r_4.get_all_orbits());
  cout<< "The ANF of rsym1 is "<<rsym1.get_anf()<<endl;
  cout<< "The degree of rsym1 is "<<rsym1.get_degree()<<endl;
  
  BooleanFunDecoder rsym2(4,"0");
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

  BooleanFunDecoder f8_rand(8);
  f8_rand.set_truth_table_random();
  cout << "Generate a random 8-variable Boolean function" << endl;
  cout << f8_rand.get_truth_table_hex() << endl;
  cout << "Gowers norm u3 is " << f8_rand.Gowers_norm_u3() << endl;
  cout << "End of test for Gowers norm u3 of a random 8-variable Boolean function" << endl;
  
  BooleanFunDecoder f9_7(9);
  f9_7.set_truth_table_hex("E9BF9F2C857E25F98568CB9BCCB8AD8DD74612AAD98DF0C56514AA56E5917B42F57F1C2268D106F37E8BC5D8E28483396430F033D3CA1ED4EBB38D8EC56308ED");
  f9_7.set_truth_table_done();
  assert(f9_7.get_degree()==7);
  assert(f9_7.nonlinearity()==242);
  BooleanFun sub0_f9_7 = f9_7.sub_function(0);
  BooleanFun sub1_f9_7 = f9_7.sub_function(1);
  sub0_f9_7.add(sub1_f9_7);
  int num=10000000*sub0_f9_7.Gowers_norm_u3();
  double num1=(double)num/10000000;
  assert(num1==0.0316267);

  BooleanFunDecoder f8(8);
  f8.set_truth_table_hex("1041F22E9EAA8704B157D8E90D61B34118787D93834C9BBD91C2EA7746FC5EA1");
  //f13.set_truth_table_done();
  int num2=10000000*f8.Gowers_norm_u3();
  double num3=(double)num2/10000000;
  assert(num3==0.0269603);

  BooleanFunDecoder f_const(6,"1");
  assert(float_equals(f_const.Gowers_norm_u2(),1.00));
  assert(float_equals(f_const.Gowers_norm_u3(),1.00));

  BooleanFunDecoder f_affine(7);
  f_affine.set_anf("x1+x2+x3+x6+x7+1");
  assert(float_equals(f_affine.Gowers_norm_u2(),1.00));
  assert(float_equals(f_affine.Gowers_norm_u3(),1.00));

  BooleanFunDecoder f_quard1(5,"x1x5+x2x3+x4x5+x2x5+x3x4");
  assert(float_equals(f_quard1.Gowers_norm_u3(),1.00));


  BooleanFunDecoder f1(3,"x1x2x3");
  assert(f1.second_order_nonlinearity_Fourquet_Tavernier()==1);
  vector<BooleanFun> term;
  term=f1.Fourquet_Tavernier_quadratic_list_decoding(2);
  assert(term.size()==8);
  assert(vector_of_bfs_contasins_anf("0",term));
  assert(vector_of_bfs_contasins_anf("x2x3",term));
  assert(vector_of_bfs_contasins_anf("x1x3",term));
  assert(vector_of_bfs_contasins_anf("x3+x2x3+x1x3",term));
  assert(vector_of_bfs_contasins_anf( "x1x2",term));
  assert(vector_of_bfs_contasins_anf("x2+x2x3+x1x2",term));
  assert(vector_of_bfs_contasins_anf( "x1+x1x3+x1x2",term));
  assert(vector_of_bfs_contasins_anf("1+x3+x2+x2x3+x1+x1x3+x1x2",term));

  vector<BooleanFun> term1;
  term1=f1.quadratic_list_decoding_brute_force(2);  
  assert(term1.size()==8);
  assert(vector_of_bfs_contasins_anf("0",term1));
  assert(vector_of_bfs_contasins_anf("x2x3",term1));
  assert(vector_of_bfs_contasins_anf("x1x3",term1));
  assert(vector_of_bfs_contasins_anf("x3+x2x3+x1x3",term1));
  assert(vector_of_bfs_contasins_anf("x1x2",term1));
  assert(vector_of_bfs_contasins_anf("x2+x2x3+x1x2",term1));
  assert(vector_of_bfs_contasins_anf("x1+x1x3+x1x2",term1));
  assert(vector_of_bfs_contasins_anf("1+x3+x2+x2x3+x1+x1x3+x1x2",term1));

  BooleanFunDecoder f2(3,"x1x2x3+x1+x2x3");
  assert(f2.nonlinearity(2)==1);
  assert(f2.second_order_nonlinearity_Fourquet_Tavernier()==1);
  vector<BooleanFun> term3;
  term3=f2.Fourquet_Tavernier_quadratic_list_decoding(2);
  assert(term3.size()==8);
  assert(vector_of_bfs_contasins_anf("x1",term3));
  assert(vector_of_bfs_contasins_anf("x2x3+x1",term3));
  assert(vector_of_bfs_contasins_anf("x3+x1+x1x3",term3));
  assert(vector_of_bfs_contasins_anf("x2x3+x1+x1x3",term3));
  assert(vector_of_bfs_contasins_anf("x2+x1+x1x2",term3));
  assert(vector_of_bfs_contasins_anf("x2x3+x1+x1x2",term3));
  assert(vector_of_bfs_contasins_anf( "1+x3+x2+x1x3+x1x2",term3));
  assert(vector_of_bfs_contasins_anf("x2x3+x1x3+x1x2",term3));

  vector<BooleanFun> term4;
  term4=f2.quadratic_list_decoding_brute_force(2);
  assert(term4.size()==8);
  assert(vector_of_bfs_contasins_anf("x1",term4));
  assert(vector_of_bfs_contasins_anf("x2x3+x1",term4));
  assert(vector_of_bfs_contasins_anf("x3+x1+x1x3",term4));
  assert(vector_of_bfs_contasins_anf( "x2x3+x1+x1x3",term4));
  assert(vector_of_bfs_contasins_anf("x2+x1+x1x2",term4));
  assert(vector_of_bfs_contasins_anf("x2x3+x1+x1x2",term4));
  assert(vector_of_bfs_contasins_anf("1+x3+x2+x1x3+x1x2",term4));
  assert(vector_of_bfs_contasins_anf("x2x3+x1x3+x1x2",term4));

  BooleanFunDecoder f3(4,"x1x2x3+x4");
  assert(f3.second_order_nonlinearity_Fourquet_Tavernier()==2);
  vector<BooleanFun> term5;
  term5=f3.Fourquet_Tavernier_quadratic_list_decoding(3);
  assert(term5.size()==8);
  assert(vector_of_bfs_contasins_anf("x4",term5));
  assert(vector_of_bfs_contasins_anf("x4+x2x3",term5));
  assert(vector_of_bfs_contasins_anf( "x4+x1x3",term5));
  assert(vector_of_bfs_contasins_anf("x4+x3+x2x3+x1x3",term5));
  assert(vector_of_bfs_contasins_anf("x4+x1x2",term5));
  assert(vector_of_bfs_contasins_anf( "x4+x2+x2x3+x1x2",term5));
  assert(vector_of_bfs_contasins_anf("x4+x1+x1x3+x1x2",term5));
  assert(vector_of_bfs_contasins_anf("1+x4+x3+x2+x2x3+x1+x1x3+x1x2",term5));

  vector<BooleanFun> term6;
  term6=f3.quadratic_list_decoding_brute_force(3);
  assert(term6.size()==8);
  assert(vector_of_bfs_contasins_anf("x4",term6));
  assert(vector_of_bfs_contasins_anf("x4+x2x3",term6));
  assert(vector_of_bfs_contasins_anf("x4+x1x3",term6));
  assert(vector_of_bfs_contasins_anf("x4+x3+x2x3+x1x3",term6));
  assert(vector_of_bfs_contasins_anf("x4+x1x2",term6));
  assert(vector_of_bfs_contasins_anf("x4+x2+x2x3+x1x2",term6));
  assert(vector_of_bfs_contasins_anf("x4+x1+x1x3+x1x2",term6));
  assert(vector_of_bfs_contasins_anf( "1+x4+x3+x2+x2x3+x1+x1x3+x1x2",term6));

  BooleanFunDecoder f4(4,"x1x2x4+x3x4");
  assert(f4.second_order_nonlinearity_Fourquet_Tavernier()==2);
  vector<BooleanFun> term7;
  term7=f4.Fourquet_Tavernier_quadratic_list_decoding(3);
  assert(term7.size()==8);
  assert(vector_of_bfs_contasins_anf("x3x4",term7));
  assert(vector_of_bfs_contasins_anf("x3x4+x2x4",term7));
  assert(vector_of_bfs_contasins_anf("x3x4+x1x4",term7));
  assert(vector_of_bfs_contasins_anf("x4+x3x4+x2x4+x1x4",term7));
  assert(vector_of_bfs_contasins_anf("x3x4+x1x2",term7));
  assert(vector_of_bfs_contasins_anf("x3x4+x2+x2x4+x1x2",term7));
  assert(vector_of_bfs_contasins_anf("x3x4+x1+x1x4+x1x2",term7));
  assert(vector_of_bfs_contasins_anf("1+x4+x3x4+x2+x2x4+x1+x1x4+x1x2",term7));

  vector<BooleanFun> term8;
  term8=f4.quadratic_list_decoding_brute_force(3);
  assert(term8.size()==8);
  assert(vector_of_bfs_contasins_anf("x3x4",term8));
  assert(vector_of_bfs_contasins_anf("x3x4+x2x4",term8));
  assert(vector_of_bfs_contasins_anf( "x3x4+x1x4",term8));
  assert(vector_of_bfs_contasins_anf("x4+x3x4+x2x4+x1x4",term8));
  assert(vector_of_bfs_contasins_anf( "x3x4+x1x2",term8));
  assert(vector_of_bfs_contasins_anf( "x3x4+x2+x2x4+x1x2",term8));
  assert(vector_of_bfs_contasins_anf("x3x4+x1+x1x4+x1x2",term8));
  assert(vector_of_bfs_contasins_anf("1+x4+x3x4+x2+x2x4+x1+x1x4+x1x2",term8));

  tStart = clock();
  BooleanFunDecoder f8_1(8);
  f8_1.set_truth_table_hex("02080292010B940B0104019EA45131AE20261343101685DA8A7346162F26BAEA");
  f8_1.set_truth_table_done();
  assert(f8_1.second_order_nonlinearity_Fourquet_Tavernier()==88);
  assert(f8_1.get_degree()==4);

  BooleanFunDecoder f8_2(8);
  f8_2.set_truth_table_hex("6BBCBCF2BFC2FD19BFCDC119CDD62697BCCEF2D5F11516A7C2E5D56B295B977C");
  f8_2.set_truth_table_done();
  assert(f8_2.second_order_nonlinearity_Fourquet_Tavernier()==88);
  assert(f8_2.get_degree()==4);

  BooleanFunDecoder f8_3(8);
  f8_3.set_truth_table_hex("7DF5ED65E8C64B56FA81C37B53BD657BDD998236E13F7D9F552E9FD75A776FBD");
  f8_3.set_truth_table_done();
  assert(f8_3.second_order_nonlinearity_Fourquet_Tavernier()==88);
  assert(f8_3.get_degree()==4);

  BooleanFunDecoder f8_4(8);
  f8_4.set_truth_table_hex("81363C783CD14DA33FD2D40641C5992D1ECCC51BF64211596017E25587A539D4");
  f8_4.set_truth_table_done();
  assert(f8_4.second_order_nonlinearity_Fourquet_Tavernier()==88);
  assert(f8_4.get_degree()==4);
  cout << "Done with nl2 for n = 8" << endl;
  cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " sec." << endl;

  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}
