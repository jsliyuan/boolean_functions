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

  vector<int> bin;
  bin=r.get_orbit(3);
  cout<<"The orbit of i is ";
  for(int i=0;i<9;i++) {
    cout<< bin[i] <<" ";
  }
  cout<<endl;

  vector<int> bin1;
  bin1=r.get_orbit_order(3);
  cout<<"The ith orbit is ";
  for(int i=0;i<9;i++) {
    cout<< bin1[i] <<" ";
  }
  cout<<endl;

  RotationSym t(6);
  assert(t.get_n() == 6);
  cout << "Everything looks good. End of all tests." << endl;
  cout<<t.get_orbits_number()<<endl;
  cout << "Everything looks good. End of all tests." << endl;

  vector<int> bin2;
  bin2=t.get_orbit(56);
  cout<<"The orbit of i is ";
  for(int i=0;i<6;i++) {
    cout<< bin2[i] <<" ";
  }
  cout<<endl;

  RotationSym t1(t);
  assert(t.get_n() == 6);
  cout << "Everything looks good. End of all tests." << endl;
  cout<<t.get_orbits_number()<<endl;
  cout << "Everything looks good. End of all tests." << endl;

  vector<int> bin3;
  bin3=t.get_orbit(56);
  cout<<"The orbit of i is ";
  for(int i=0;i<6;i++) {
    cout<< bin3[i] <<" ";
  }
  cout<<endl;

  RotationSym r1(11);
  assert(r1.get_n() == 11);
  cout << "Everything looks good. End of all tests." << endl;
  cout<<r1.get_orbits_number()<<endl;
  cout << "Everything looks good. End of all tests." << endl;

  vector<int> bin4;
  bin4=r1.get_orbit_order(175);
  cout<<"The ith orbit of is ";
  for(int i=0;i<11;i++) {
    cout<< bin4[i] <<" ";
  }
  cout<<endl;
  return 0;
}
