#include <iostream>
#include <time.h>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <utility>

#include "boolean_fun.h"
#include "permutation.h"
#include "perm_group.h"

using namespace std;

int main() {
  BooleanFun f(9);
  PermGroup PG(9);
  Permutation perm(9);
  perm.set("1,3,2,5,6,7,8,9,4");
  PG.set_generator(perm);
  PG.compute_orbits();
  // Initialize f at random

  for (int run=0; run< 20; run++) {
  f.set_random_sym(PG.get_all_orbits());
  
  set<pair<int, BooleanFun> > store; 
  set<pair<int, BooleanFun> > visited; 
  std::pair<int, BooleanFun> cur(f.cost(),f);
  visited.insert(cur);
  int max_value=0;
  string max_truth_table;
  // Local search from f
  for(int round=0; round<100000; round++) {
    for (int count=0; count < 104;count++) {
      vector<int> bin;
      bin=PG.get_full_orbit(count);

      BooleanFun f_son(9);
      f_son=f;

      int* term;
      term=f_son.truth_table;

      if(term[bin[0]]==1){
        f_son.set_truth_table_orbit(bin,0);
      }
      else {
        f_son.set_truth_table_orbit(bin,1);
      }

      std::pair<int,BooleanFun> p(f_son.cost(),f_son);
      if(visited.find(p)==visited.end())
      {
        store.insert(p);
        visited.insert(p);
      }
    }
    std:: pair<int,BooleanFun> target((*store.begin()).first,(*store.begin()).second);
    f=(*store.begin()).second;
    store.erase(target);
  }
  cout<< "run is "<< run<<" nonlinearity: "<<max_value<<endl;
  cout<<max_truth_table<<endl;
  }
  return 0;
}
