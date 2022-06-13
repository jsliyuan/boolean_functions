#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <vector>

#include "rotationsym.h"
#include "permutation.h"

using namespace std;

int main() {
  RotationSym r(9);
  assert(r.get_n() == 9);
  cout << "Everything looks good. End of all tests." << endl;
  cout<<r.get_orbits_number()<<endl;
  cout << "Everything looks good. End of all tests." << endl;

  //r.get_orbit(1);

  /*RotationSym t(6);
  assert(t.get_n() == 6);
  cout << "Everything looks good. End of all tests." << endl;
  cout<<t.get_orbits_number()<<endl;
  cout << "Everything looks good. End of all tests." << endl;*/
  return 0;
}
