#include "affine_trans.h"

#include <iostream>
#include <unordered_set>

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
  assert(t3_perm.get_a_row(0) == -1);
  assert(t3_perm.get_a_row(1) == 4);
  assert(t3_perm.get_a_row(2) == 2);
  assert(t3_perm.get_a_row(3) == 1);
  assert(t3_perm.get_a_row(4) == -1);
  assert(t3_perm.set_b(1,1));
  assert(t3_perm.get_b_str() == "1 0 0");
  for (int i = 0; i < (1<<3); i ++) {
    int i3 = i%2;
    int i2 = (i/2)%2;
    int i1 = (i/4)%2;
    assert(t3_perm.apply(i) == (1-i3)*4+i2*2+i1);
  }
  cout << "End of test for t3_perm" << endl;

  // t4_upp sends (x1, x2, x3, x4) to (x1+x2+x3+x4, x2+x3+x4, x3+x4, x4)
  AffineTrans t4_upp(4);
  for (int i = 1; i <= t4_upp.get_n(); i ++) {
  	for (int j = i; j <= t4_upp.get_n(); j ++) {
      assert(t4_upp.set_a(i,j,1));
    }
  }
  for (int i = 0; i < (1<<4); i ++) {
    int i4 = i%2;
    int i3 = (i/2)%2;
    int i2 = (i/4)%2;
    int i1 = (i/8)%2;
    int y4 = i4;
    int y3 = (i3+i4)%2;
    int y2 = (i2+y3)%2;
    int y1 = (i1+y2)%2;
    assert(t4_upp.apply(i) == y1*8+y2*4+y3*2+y4); 
  }
  cout << "End of test for t4_upp" << endl;

  AffineTrans t4_identity(4);
  assert(t4_identity.set_row_a(1, 1));
  assert(t4_identity.set_row_a(2, 2));
  assert(t4_identity.set_row_a(3, 4));
  assert(t4_identity.set_row_a(4, 8));
  assert(t4_identity.set_row_a(4, 16) == false);
  assert(t4_identity.set_row_a(4, -1) == false);
  assert(t4_identity.set_row_a(0, 1) == false);
  assert(t4_identity.set_row_a(5, 1) == false);
  assert(t4_identity.get_a_str() == "1 0 0 0\n0 1 0 0\n0 0 1 0\n0 0 0 1");
  cout << "End of test for t4_identity" << endl;


  AffineTrans t3_identity(3);
  assert(t3_identity.set_row_a(1, 7));
  assert(t3_identity.set_row_a(2, 2));
  assert(t3_identity.set_row_a(3, 4));
  assert(t3_identity.get_a_str() == "1 1 1\n0 1 0\n0 0 1");
  unordered_set<int> span = t3_identity.get_rows_span(1, 3);
  assert(span.size() == 8);
  for (int i = 0; i < 8; i ++) {
    assert(span.find(i) != span.end());
  }

  assert(t3_identity.set_row_a(2, 7));
  span = t3_identity.get_rows_span(1, 3);
  assert(span.size() == 4);
  assert(span.find(0) != span.end());
  assert(span.find(4) != span.end());
  assert(span.find(7) != span.end());
  assert(span.find(3) != span.end());

  span = t3_identity.get_rows_span(3, 1);
  assert(span.size() == 1);
  assert(span.find(0) != span.end());

  cout << "Everything looks good. End of all tests." << endl;

  return 0;
}
