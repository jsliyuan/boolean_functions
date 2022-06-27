#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <vector>

#include "SymGroup.h"
#include "permutation.h"

using namespace std;

int main() {
  SymGroup SG(9);
  Permutation perm(9);
  perm.set("9,8,4,1,2,7,3,5,6");
  assert(SG.get_n() ==9);
  SG.set_generator(perm);
  SG.compute_orbits();
  vector<Permutation> bin1;
  bin1=SG.get_elements();
  for (const Permutation& perm1:bin1) {
    cout<<perm1.get_str()<<endl;
  }
  cout<<SG.get_orbits_number() <<" "<< SG.group_size()<<endl;

  SymGroup SG1(9);
  Permutation perm1(9);
  perm1.set("5,7,8,3,9,2,6,4,1");
  assert(SG1.get_n() ==9);
  SG1.set_generator(perm1);
  SG1.compute_orbits();
  vector<Permutation> bin;
  bin=SG1.get_elements();
  for (const Permutation& perm2:bin) {
    cout<<perm2.get_str()<<endl;
  }
  cout<<SG1.get_orbits_number() <<" "<< SG1.group_size()<<endl;

  SymGroup SG2(9);
  Permutation perm2(9);
  perm2.set("2,5,8,6,7,3,1,4,9");
  assert(SG2.get_n() ==9);
  SG2.set_generator(perm2);
  SG2.compute_orbits();
  vector<Permutation> bin2;
  bin2=SG2.get_elements();
  for (const Permutation& perm3:bin2) {
    cout<<perm3.get_str()<<endl;
  }
  cout<<SG2.get_orbits_number() <<" "<< SG2.group_size()<<endl;

  SymGroup SG3(9);
  Permutation perm3(9);
  perm3.set("1,3,2,5,6,7,8,9,4");
  assert(SG3.get_n() ==9);
  SG3.set_generator(perm3);
  SG3.compute_orbits();
  vector<Permutation> bin3;
  bin3=SG3.get_elements();
  for (const Permutation& perm4:bin3) {
    cout<<perm4.get_str()<<endl;
  }
  cout<<SG3.get_orbits_number() <<" "<< SG3.group_size()<<endl;
  cout<< "Everything looks good. End of all tests." << endl;
  return 0;
}
