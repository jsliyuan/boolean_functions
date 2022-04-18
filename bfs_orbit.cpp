#include "boolean_fun.h"
#include "affine_trans.h"

#include <iostream>
#include <set>
#include <vector>

using namespace std;

int count_all_mod_rm36(string fni) {
  // Generators for affine linear groups.
  // See "Two generators for the general linear groups over finite fields" by William C. Waterhouse
  vector<AffineTrans> generators;
  AffineTrans *g1 = new AffineTrans(6, "[100000 010000 001000 000100 000010 100001]000000");
  generators.push_back(*g1);
  AffineTrans *g2 = new AffineTrans(6, "[010000 001000 000100 000010 000001 100000]000000");
  generators.push_back(*g2);
  AffineTrans *g3 = new AffineTrans(6, "[100000 010000 001000 000100 000010 000001]100000");
  generators.push_back(*g3);

  // coe list of each Boolean function, as queue
  vector<string> queue;
  set<string> all_bfs;
  int total = 0;

  // Use BFS to recover the orbit of fni
  BooleanFun fn_start(6, fni);
  queue.push_back(fn_start.get_coe_list());
  int idx = 0;
  while (idx < queue.size()) {
    string coe_list = queue.at(idx);
    BooleanFun fn1(6);
    for (const AffineTrans& T : generators) {
      fn1.set_coe_list(coe_list);
      fn1.apply_affine_trans(T);
      fn1.trim_degree_below(4);
      string new_coe = fn1.get_coe_list();
      if (all_bfs.find(new_coe) == all_bfs.end()) {
        all_bfs.insert(new_coe);
        queue.push_back(new_coe);
        total ++;
        // cout << total << endl;
        if (total % 10000 == 0) {
          cout << total << endl;
        }
      }
    }

    idx ++;
  }
  return total;
}

int count_all_mod_rm36_and_save_affine(string fni) {
  // Generators for affine linear groups.
  // See "Two generators for the general linear groups over finite fields" by William C. Waterhouse
  vector<AffineTrans> generators;
  AffineTrans *g1 = new AffineTrans(6, "[100000 010000 001000 000100 000010 100001]000000");
  generators.push_back(*g1);
  AffineTrans *g2 = new AffineTrans(6, "[010000 001000 000100 000010 000001 100000]000000");
  generators.push_back(*g2);
  AffineTrans *g3 = new AffineTrans(6, "[100000 010000 001000 000100 000010 000001]100000");
  generators.push_back(*g3);

  // coe list of each Boolean function, as queue
  vector<string> queue;
  set<string> all_bfs;
  vector<AffineTrans> queue_affine;

  // count the number of distinct A's
  set<string> distinct_A;
  int total_a = 0;

  // Total number of functions
  int total = 0;

  // Use BFS to recover the orbit of fni
  BooleanFun fn_start(6, fni);
  queue.push_back(fn_start.get_coe_list());
  AffineTrans t6_identity(6, "[100000 010000 001000 000100 000010 000001]000000");
  queue_affine.push_back(t6_identity);
  distinct_A.insert(t6_identity.get_a_str());
  int idx = 0;
  while (idx < queue.size()) {
    string coe_list = queue.at(idx);
    BooleanFun fn1(6);
    for (const AffineTrans& T : generators) {
      fn1.set_coe_list(coe_list);
      fn1.apply_affine_trans(T);
      fn1.trim_degree_below(4);
      string new_coe = fn1.get_coe_list();
      if (all_bfs.find(new_coe) == all_bfs.end()) {
        all_bfs.insert(new_coe);
        queue.push_back(new_coe);
        AffineTrans *new_aft = new AffineTrans(queue_affine.at(idx));
        new_aft->mult(T);
        queue_affine.push_back(*new_aft);

        // Track distinct A's
        string a_str = new_aft->get_a_str();
        if (distinct_A.find(a_str) == distinct_A.end()) {
          distinct_A.insert(a_str);
          total_a ++;
          // Print the affine transformation
          cout << new_aft->get_ab_str() << endl;
        }

        // cout << new_aft->get_ab_str() << endl;
        // For verification only
        BooleanFun fnv(6, fni);
        fnv.apply_affine_trans(*new_aft);
        fnv.trim_degree_below(4);
        assert(fnv.get_coe_list() == new_coe);

        total ++;
        /*
        if (total % 10000 == 0) {
          cout << total << endl;
        }
        */
      }
    }

    idx ++;
  }

  cout << total_a << endl;

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
  // cout << count_all_mod_rm36_and_save_affine("x1x2x3x4x5x6+x2x3x4x5+x1x3x4x6+x1x2x5x6") << endl;
  cout << count_all_mod_rm36_and_save_affine("x1x2x3x4x5x6+x2x3x4x5+x1x3x4x6+x1x2x5x6") << endl;

  return 0;
}