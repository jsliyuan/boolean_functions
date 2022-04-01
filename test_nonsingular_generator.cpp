#include "nonsingular_generator.h"

#include <iostream>
#include <cassert>

using namespace std;

int main() {
  NonsingularGenerator gen1(1);
  assert(gen1.get_affine_trans()->get_a_str() == "1");
  assert(gen1.next() == false);
  cout << "End of test for gen1" << endl;

  NonsingularGenerator gen2(2);
  assert(gen2.get_affine_trans()->get_a_str() == "0 1\n1 0");
  assert(gen2.next() == true);
  assert(gen2.get_affine_trans()->get_a_str() == "1 1\n1 0");
  assert(gen2.next() == true);
  assert(gen2.get_affine_trans()->get_a_str() == "1 0\n0 1");
  assert(gen2.next() == true);
  assert(gen2.get_affine_trans()->get_a_str() == "1 1\n0 1");
  assert(gen2.next() == true);
  assert(gen2.get_affine_trans()->get_a_str() == "1 0\n1 1");
  assert(gen2.next() == true);
  assert(gen2.get_affine_trans()->get_a_str() == "0 1\n1 1");
  assert(gen2.next() == false);
  cout << "End of test for gen2" << endl;

  NonsingularGenerator gen3(3);
  assert(gen3.get_affine_trans()->get_a_str() == "0 0 1\n0 1 0\n1 0 0");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "1 0 1\n0 1 0\n1 0 0");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "0 1 1\n0 1 0\n1 0 0");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "1 1 1\n0 1 0\n1 0 0");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "0 0 1\n1 1 0\n1 0 0");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "1 0 1\n1 1 0\n1 0 0");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "0 1 1\n1 1 0\n1 0 0");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "1 1 1\n1 1 0\n1 0 0");
  assert(gen3.next() == true);
  assert(gen3.get_affine_trans()->get_a_str() == "0 1 0\n0 0 1\n1 0 0");
  assert(gen3.next() == true);
  cout << "End of test for gen3" << endl;

  gen3.init();
  int total = 0;
  do {
    total ++;
  } while (gen3.next());
  assert(total == 7 * 6 * 4);
  cout << "End of test for enumerating all 3*3" << endl;

  NonsingularGenerator gen4(4);
  total = 0;
  do {
    total ++;
  } while (gen4.next());
  assert(total == 15 * 14 * 12 * 8);
  cout << "End of test for enumerating all 4*4" << endl;

  NonsingularGenerator gen5(5);
  total = 0;
  do {
    total ++;
    if (total % 100000 == 0) {
      cout << "Enumerating..., total = " << total << endl;
    }
  } while (gen5.next());
  assert(total == 9999360);
  cout << "End of test for enumerating all 5*5" << endl;

  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}
