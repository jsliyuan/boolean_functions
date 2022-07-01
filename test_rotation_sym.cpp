#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <vector>
#include <cassert>

#include "rotation_sym.h"
#include "permutation.h"

using namespace std;

int main() {
  RotationSym r1(3);
  assert(r1.get_n() ==3);
  assert(r1.get_orbits_number()==4);
  // TODO(yl): upgrade g++ compiler
  // vector<vector<int> > binv{{0},{1,2,4},{3,6,5},{7}};
  vector<vector<int> > binv;
  vector<int> binv1;
  binv1.push_back(0);
  binv.push_back(binv1);
  vector<int> binv2;
  binv2.push_back(1);
  binv2.push_back(2);
  binv2.push_back(4);
  binv.push_back(binv2);
  vector<int> binv3;
  binv3.push_back(3);
  binv3.push_back(6);
  binv3.push_back(5);
  binv.push_back(binv3);
  vector<int> binv4;
  binv4.push_back(7);
  binv.push_back(binv4);
  assert(r1.get_all_orbits()==binv);

  RotationSym r(9);
  assert(r.get_n() == 9);
  assert(r.get_orbits_number()==60);
  // TODO(yl): upgrade g++ compiler
  // vector<int> bin{3,6,12,24,48,96,192,384,257};
  vector<int> bin;
  bin.push_back(3);
  bin.push_back(6);
  bin.push_back(12);
  bin.push_back(24);
  bin.push_back(48);
  bin.push_back(96);
  bin.push_back(192);
  bin.push_back(384);
  bin.push_back(257);
  assert(r.get_orbit(3)==bin );
  
  // TODO(yl): upgrade g++ compiler
  // vector<int> bin_1{5,10,20,40,80,160,320,129,258};
  vector<int> bin_1;
  bin_1.push_back(5);
  bin_1.push_back(10);
  bin_1.push_back(20);
  bin_1.push_back(40);
  bin_1.push_back(80);
  bin_1.push_back(160);
  bin_1.push_back(320);
  bin_1.push_back(129);
  bin_1.push_back(258);
  assert(r.get_full_orbit(3)==bin_1);

  RotationSym t(6);
  assert(t.get_n() == 6);
  assert(t.get_orbits_number()==14);
  // TODO(yl): upgrade g++ compiler
  // vector<int> bin_2{56,49,35,7,14,28};
  vector<int> bin_2;
  bin_2.push_back(56);
  bin_2.push_back(49);
  bin_2.push_back(35);
  bin_2.push_back(7);
  bin_2.push_back(14);
  bin_2.push_back(28);
  assert(t.get_orbit(56)==bin_2);

  RotationSym t1(t);
  assert(t1.get_n() == 6);
  assert(t1.get_orbits_number()==14);
  // TODO(yl): upgrade g++ compiler
  // vector<int> bin_3{56,49,35,7,14,28};
  vector<int> bin_3;
  bin_3.push_back(56);
  bin_3.push_back(49);
  bin_3.push_back(35);
  bin_3.push_back(7);
  bin_3.push_back(14);
  bin_3.push_back(28);
  assert(t1.get_orbit(56)==bin_3);

  RotationSym r11(11);
  assert(r11.get_n() == 11);
  assert(r11.get_orbits_number()==188);
  // TODO(yl): upgrade g++ compiler
  // vector<int> bin_4{731,1462, 877, 1754, 1461, 875, 1750, 1453, 859, 1718, 1389};
  vector<int> bin_4;
  bin_4.push_back(731);
  bin_4.push_back(1462);
  bin_4.push_back(877);
  bin_4.push_back(1754);
  bin_4.push_back(1461);
  bin_4.push_back(875);
  bin_4.push_back(1750);
  bin_4.push_back(1453);
  bin_4.push_back(859);
  bin_4.push_back(1718);
  bin_4.push_back(1389);
  assert(r11.get_full_orbit(175)==bin_4);
  
  cout<< "Everything looks good. End of all tests." << endl;
  return 0;
}
