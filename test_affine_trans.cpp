#include "affine_trans.h"

#include <iostream>

using namespace std;

int main() {
  AffineTrans t3_zero(3);
  assert(t3_zero.get_n() == 3);

  assert(t3_zero.get_a(0, 1) == -1);
  assert(t3_zero.get_a(4, 1) == -1);
  assert(t3_zero.get_a(1, 0) == -1);
  assert(t3_zero.get_a(1, 5) == -1);
  assert(t3_zero.get_a(1, 1) == 0);
  assert(t3_zero.get_a_str() == "0 0 0\n0 0 0\n0 0 0");

  assert(t3_zero.get_b(0) == -1);
  assert(t3_zero.get_b(4) == -1);
  assert(t3_zero.get_b(2) == 0);
  assert(t3_zero.get_b_str() == "0 0 0");

  assert(t3_zero.apply(-1) == -1);
  assert(t3_zero.apply(8) == -1);
  assert(t3_zero.apply(7) == 0);
  cout << "End of test for t3_zero" << endl;

  // t3_diag sends (x1,x2,x3) to (x1+1,x2,x3).
  AffineTrans t3_diag(3);
  assert(t3_diag.get_n() == 3);

  assert(t3_diag.set_a(1,1,1));
  assert(t3_diag.set_a(2,2,1));
  assert(t3_diag.set_a(3,3,1));
  assert(t3_diag.get_a_str() == "1 0 0\n0 1 0\n0 0 1");

  assert(t3_diag.set_b(1,1));
  assert(t3_diag.set_b(2,1));
  assert(t3_diag.set_b(3,1));
  assert(t3_diag.get_b_str() == "1 1 1");
  for (int i = 0; i < (1<<3); i ++) {
  	assert(t3_diag.apply(i) == 7 - i);
  }
  cout << "End of test for t3_diag" << endl;

  // t3_perm sends (x1, x2, x3) to (x3+1, x2, x1)
  AffineTrans t3_perm(3);
  assert(t3_perm.set_a(1,3,1));
  assert(t3_perm.set_a(2,2,1));
  assert(t3_perm.set_a(3,1,1));
  assert(t3_perm.get_a_str() == "0 0 1\n0 1 0\n1 0 0");
  assert(t3_perm.set_b(1,1));
  assert(t3_perm.get_b_str() == "1 0 0");
  for (int i = 0; i < (1<<3); i ++) {
  	int i3 = i%2;
  	int i2 = (i/2)%2;
  	int i1 = (i/4)%2;
  	assert(t3_perm.apply(i) == (1-i3)*4+i2*2+i1);
  }
  cout << "End of test for t3_perm" << endl;

  cout << "Everything looks good. End of all tests." << endl;

  return 0;
}