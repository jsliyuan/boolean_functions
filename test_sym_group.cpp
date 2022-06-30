#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <vector>

#include "sym_group.h"
#include "permutation.h"

using namespace std;

int main() {
  SymGroup SG(9);
  Permutation perm(9);
  perm.set("9,8,4,1,2,7,3,5,6");
  assert(SG.get_n() ==9);
  SG.set_generator(perm);
  SG.compute_orbits();
  assert(SG.group_size()==6);
  assert(SG.get_orbits_number()==100);
  vector<Permutation> bin1;
  bin1=SG.get_elements();
  assert(bin1[0].get_str()=="1,2,3,4,5,6,7,8,9");
  assert(bin1[2].get_str()=="6,5,1,9,8,3,4,2,7");
  assert(bin1[5].get_str()=="4,5,7,3,8,9,6,2,1");

  SymGroup SG1(9);
  Permutation perm1(9);
  perm1.set("5,7,8,3,9,2,6,4,1");
  assert(SG1.get_n() ==9);
  SG1.set_generator(perm1);
  SG1.compute_orbits();
  assert(SG1.group_size()==3);
  assert(SG1.get_orbits_number()==176);
  vector<Permutation > bin;
  bin=SG1.get_elements();
  assert(bin[0].get_str()=="1,2,3,4,5,6,7,8,9");
  assert(bin[1].get_str()=="5,7,8,3,9,2,6,4,1");
  assert(bin[2].get_str()=="9,6,4,8,1,7,2,3,5");

  SymGroup SG2(9);
  Permutation perm2(9);
  perm2.set("2,5,8,6,7,3,1,4,9");
  assert(SG2.get_n() ==9);
  SG2.set_generator(perm2);
  SG2.compute_orbits();
  assert(SG2.group_size()==4);
  assert(SG2.get_orbits_number()==140);
  vector<Permutation> bin2;
  bin2=SG2.get_elements();
  assert(bin2[0].get_str()=="1,2,3,4,5,6,7,8,9");
  assert(bin2[1].get_str()=="2,5,8,6,7,3,1,4,9");
  assert(bin2[2].get_str()=="5,7,4,3,1,8,2,6,9");
  assert(bin2[3].get_str()=="7,1,6,8,2,4,5,3,9");

  SymGroup SG3(9);
  Permutation perm3(9);
  perm3.set("1,3,2,5,6,7,8,9,4");
  assert(SG3.get_n() ==9);
  SG3.set_generator(perm3);
  SG3.compute_orbits();
  assert(SG3.group_size()==6);
  assert(SG3.get_orbits_number()==104);
  vector<Permutation> bin3;
  bin3=SG3.get_elements();
  assert(bin3[1].get_str()=="1,3,2,5,6,7,8,9,4");
  assert(bin3[2].get_str()=="1,2,3,6,7,8,9,4,5");
  assert(bin3[3].get_str()=="1,3,2,7,8,9,4,5,6");
  assert(bin3[4].get_str()=="1,2,3,8,9,4,5,6,7");

  cout<< "Everything looks good. End of all tests." << endl;
  return 0;
}
