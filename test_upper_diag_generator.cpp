#include "upper_diag_generator.h"

#include <iostream>
#include <assert.h>
#include <cassert>

using namespace std;

int main() {
  UpperDiagGenerator gen1(1);
  assert(gen1.get_affine_trans()->get_a_str() == "1");
  assert(gen1.next() == false);
  cout << "End of test for gen1" << endl;

  UpperDiagGenerator gen2(2);
  assert(gen2.get_affine_trans()->get_a_str() == "1 0\n0 1");
  assert(gen2.next() == true);
  assert(gen2.get_affine_trans()->get_a_str() == "1 1\n0 1");
  assert(gen2.next() == false);
  cout << "End of test for gen2" << endl;

  UpperDiagGenerator gen3(3);
  assert(gen3.get_affine_trans()->get_a_str() == "1 0 0\n0 1 0\n0 0 1");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "1 1 0\n0 1 0\n0 0 1");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "1 0 1\n0 1 0\n0 0 1");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "1 1 1\n0 1 0\n0 0 1");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "1 0 0\n0 1 1\n0 0 1");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "1 1 0\n0 1 1\n0 0 1");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "1 0 1\n0 1 1\n0 0 1");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "1 1 1\n0 1 1\n0 0 1");
  assert(gen3.next() == false);
  cout << "End of test for gen3" << endl;

  UpperDiagGenerator gen4(4);
  assert(gen4.get_affine_trans()->get_a_str() == "1 0 0 0\n0 1 0 0\n0 0 1 0\n0 0 0 1");
  assert(gen4.next() == true);
  assert(gen4.get_affine_trans()->get_a_str() == "1 1 0 0\n0 1 0 0\n0 0 1 0\n0 0 0 1");
  assert(gen4.next() == true);
  assert(gen4.get_affine_trans()->get_a_str() == "1 0 1 0\n0 1 0 0\n0 0 1 0\n0 0 0 1");
  assert(gen4.next() == true);
  gen4.init();
  assert(gen4.get_affine_trans()->get_a_str() == "1 0 0 0\n0 1 0 0\n0 0 1 0\n0 0 0 1");
  for (int i = 0; i < (1<<6) - 1; i ++) {
    assert(gen4.next() == true);
  }
  assert(gen4.next() == false);
  cout << "End of test for gen4" << endl;

  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}