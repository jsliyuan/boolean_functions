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
  cout << count_all_mod_rm36("x1x2x3x4") << endl;
  cout << count_all_mod_rm36("x1x2x4x5+x1x2x3x6") << endl;
  cout << count_all_mod_rm36("x2x3x4x5+x1x3x4x6+x1x2x5x6") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5+x1x2x3x6") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5+x1x3x4x6+x1x2x5x6") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5x6") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5x6+x1x2x3x4") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5x6+x1x2x4x5+x1x2x3x6") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5x6+x2x3x4x5+x1x3x4x6+x1x2x5x6") << endl;
  */
  cout << count_all_mod_rm36("x1x2x4x5+x1x2x3x6") << endl;

  return 0;
}