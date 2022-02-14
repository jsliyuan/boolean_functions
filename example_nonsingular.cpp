#include "boolean_fun.h"
#include "nonsingular_generator.h"

#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
  NonsingularGenerator gen4(4);
  int total = 0;
  set<string> all_bfs;
  BooleanFun f4(4);

  while (1) {
    f4.set_anf("x1x2x3+x2x3x4");
    f4.apply_affine_trans(*gen4.get_affine_trans());
    // Trim all monomials with degree <= 2.
    f4.trim_degree_below(3);
    string anf = f4.get_anf();
    // Make sure it hasn't been added.
    if (all_bfs.find(anf) == all_bfs.end()) {
      all_bfs.insert(anf);
      cout << anf << endl;
      total ++;
    }
    if (gen4.next() == false) {
      break;
    }
  }
  cout << "total = " << total << endl;
  return 0;
}
