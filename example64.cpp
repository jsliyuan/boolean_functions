#include "boolean_fun.h"
#include "upper_diag_generator.h"

#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
  UpperDiagGenerator gen6(6);
  int total = 0;
  set<string> all_bfs;
  while (1) {
    BooleanFun f64(6, "x1x2x3x6+x1x2x4x5");
    f64.apply_affine_trans(*gen6.get_affine_trans());
    f64.trim_degree_below(4);
    string anf = f64.get_anf();
    if (all_bfs.find(anf) == all_bfs.end()) {
      all_bfs.insert(anf);
      cout << anf << endl;
      total ++;
    }
    if (gen6.next() == false) {
      break;
    }
  }
  cout << "total = " << total << endl;
  return 0;
}
