// You can use this program to produce all 6-variable Boolean functions affine equivalent to fn_i modulo RM(3,6)

#include "boolean_fun.h"
#include "affine_trans.h"

#include <iostream>
#include <set>

using namespace std;

int count_all_mod_rm36(string fni) {
  BooleanFun fn1(6);
  AffineTrans t6_rand(6);
  set<string> all_bfs;
  int total = 0;

  while (1) {
    t6_rand.set_random();
    t6_rand.set_random_b();
    fn1.set_anf(fni);
  	fn1.apply_affine_trans(t6_rand);
  	fn1.trim_degree_below(4);

  	string anf = fn1.get_anf();
  	if (all_bfs.find(anf) == all_bfs.end()) {
      all_bfs.insert(anf);
      total ++;
      cout << total << endl;
    }
  }

  return total;
}

int main() {
  /*
  fn1
  cout << count_all_mod_rm36("x1x2x3x4") << endl;
  fn2
  cout << count_all_mod_rm36("x1x2x4x5+x1x2x3x6") << endl;
  fn3
  cout << count_all_mod_rm36("x2x3x4x5+x1x3x4x6+x1x2x5x6") << endl;
  fn4
  cout << count_all_mod_rm36("x1x2x3x4x5") << endl;
  fn5
  cout << count_all_mod_rm36("x1x2x3x4x5+x1x2x3x6") << endl;
  fn6
  cout << count_all_mod_rm36("x1x2x3x4x5+x1x3x4x6+x1x2x5x6") << endl;
  fn7
  cout << count_all_mod_rm36("x1x2x3x4x5x6") << endl;
  fn8
  cout << count_all_mod_rm36("x1x2x3x4x5x6+x1x2x3x4") << endl;
  fn9
  cout << count_all_mod_rm36("x1x2x3x4x5x6+x1x2x4x5+x1x2x3x6") << endl;
  fn10
  cout << count_all_mod_rm36("x1x2x3x4x5x6+x2x3x4x5+x1x3x4x6+x1x2x5x6") << endl;
  */
  cout << count_all_mod_rm36("x1x2x3x4x5x6+x1x2x4x5+x1x2x3x6") << endl;

  return 0;
}