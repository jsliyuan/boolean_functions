#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <vector>

#include "rotationsym.h"
#include "permutation.h"

using namespace std;

int main() {
  RotationSym r1(3);
  assert(r1.get_n() ==3);
  assert(r1.get_orbits_number()==4);
  int binv1[]= {3,6,5};
  vector<int> binv=r1.get_full_orbit(2) ;
  for (int i=0;i<binv.size();i++) {
    assert(binv1[i]==binv[i]);
  }

  RotationSym r(9);
  assert(r.get_n() == 9);
  assert(r.get_orbits_number()==60);
  /*vector<vector<int> > binv;
  binv=r.get_all_orbits();
  for(vector<vector<int> >::iterator it=binv.begin();it!=binv.end();it++) {
    for(vector<int>::iterator itt=(*it).begin();itt!=(*it).end();itt++) {
      cout<<*itt<<" ";
    }
    cout<<endl;
  }*/
  int bin[]= {3,6,12,24,48,96,192,384,257};
  vector<int> bin1=r.get_orbit(3) ;
  for (int i=0;i<bin1.size();i++) {
    assert(bin1[i]==bin[i]);
  }
  int bin_1[]= {5,10,20,40,80,160,320,129,258};
  vector<int> bin1_1=r.get_full_orbit(3);
  for (int i=0;i<bin1_1.size();i++) {
    assert(bin1_1[i]==bin_1[i]);
  }

  RotationSym t(6);
  assert(t.get_n() == 6);
  assert(t.get_orbits_number()==14);
  int bin_2[]={56,49,35,7,14,28};
  vector<int> bin1_2=t.get_orbit(56);
  for (int i=0;i<bin1_2.size();i++) {
    assert(bin1_2[i]==bin_2[i]);
  }

  RotationSym t1(t);
  assert(t1.get_n() == 6);
  assert(t1.get_orbits_number()==14);
  int bin_3[]={56,49,35,7,14,28};
  vector<int> bin1_3=t1.get_orbit(56);
  for (int i=0;i<bin1_3.size();i++) {
    assert(bin1_3[i]==bin_3[i]);
  }

  RotationSym r11(11);
  assert(r11.get_n() == 11);
  assert(r11.get_orbits_number()==188);
  int bin_4[]={731,1462, 877, 1754, 1461, 875, 1750, 1453, 859, 1718, 1389};
  vector<int> bin1_4=r11.get_full_orbit(175);
  for (int i=0;i<bin1_4.size();i++) {
    assert(bin1_4[i]==bin_4[i]);
  }
  
  cout<< "Everything looks good. End of all tests." << endl;
  return 0;
}

