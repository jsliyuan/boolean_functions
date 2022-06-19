#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <vector>

#include "rotation_sym.h"
#include "permutation.h"

using namespace std;

int main() {
  RotationSym r1(3);
  assert(r1.get_n() ==3);
  assert(r1.get_orbits_number()==4);
  vector<vector<int> > binv{{0},{1,2,4},{3,6,5},{7}};
  assert(r1.get_all_orbits()==binv);

  RotationSym r(9);
  assert(r.get_n() == 9);
  assert(r.get_orbits_number()==60);
  vector<int> bin{3,6,12,24,48,96,192,384,257};
  assert(r.get_orbit(3)==bin );
  
  vector<int> bin_1{5,10,20,40,80,160,320,129,258};
  assert(r.get_full_orbit(3)==bin_1);

  RotationSym t(6);
  assert(t.get_n() == 6);
  assert(t.get_orbits_number()==14);
  vector<int> bin_2{56,49,35,7,14,28};
  assert(t.get_orbit(56)==bin_2);

  RotationSym t1(t);
  assert(t1.get_n() == 6);
  assert(t1.get_orbits_number()==14);
  vector<int> bin_3{56,49,35,7,14,28};
  assert(t1.get_orbit(56)==bin_3);

  RotationSym r11(11);
  assert(r11.get_n() == 11);
  assert(r11.get_orbits_number()==188);
  vector<int> bin_4{731,1462, 877, 1754, 1461, 875, 1750, 1453, 859, 1718, 1389};
  assert(r11.get_full_orbit(175)==bin_4);
  
  cout<< "Everything looks good. End of all tests." << endl;
  return 0;
}


