#include "boolean_fun.h"
#include "upper_diag_generator.h"

#include <iostream>

using namespace std;

int main() {
  UpperDiagGenerator gen6(6);
  int total = 0;
  while (1) {
    BooleanFun f64(6, "x1x2x3x6+x1x2x4x5");
    f64.apply_affine_trans(*gen6.get_affine_trans());
    cout << f64.get_anf() << endl;
    cout << "degree = " << f64.get_degree() << endl;
    total = total + 1;
    if (gen6.next() == false) {
      break;
    }
  }
  cout << "total = " << total << endl;
  return 0;
}