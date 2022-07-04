#include <iostream>
#include <time.h>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <utility>

#include "boolean_fun.h"
#include "permutation.h"
#include "perm_group.h"
//#include "rotation_sym.h"

using namespace std;

void Best_fs(BooleanFun seed,PermGroup PG) {
  unordered_set<string> visited;
  set<pair<int, string> > bfs_queue;
  pair<int, string> seed_pair(seed.cost(), seed.get_truth_table_hex());
  bfs_queue.insert(seed_pair);
  visited.insert(seed.get_truth_table_hex());
  int max_nonlinearity=seed.nonlinearity();
  string max_truth_table_hex=seed.get_truth_table_hex();
  const int MAX_SEARCH_SPACE = 400000;
  const int SELECT_CHILDREN_NUM = 1;
  for (int i = 0; i < MAX_SEARCH_SPACE; i ++) {
    //cout<< "round is "<<i<< endl;
    BooleanFun f(seed.var_num());
    f.set_truth_table_hex((*bfs_queue.begin()).second);
    visited.insert(f.get_truth_table_hex());
    bfs_queue.erase(bfs_queue.begin());
    set<pair<int,string> > store;
    for (int count=0; count < 140;count++) {
      vector<int> bin;
      bin=PG.get_full_orbit(count);

      BooleanFun f_son=f;

      const int* term;
      term=f_son.get_truth_table_ptr();

      if(term[bin[0]]==1) {
        f_son.set_truth_table_orbit(bin,0);
      }
      else {
        f_son.set_truth_table_orbit(bin,1);
      }
      pair<int,string> p(f_son.cost(),f_son.get_truth_table_hex());
      store.insert(p);
    }
    int j=0;
    while(j<SELECT_CHILDREN_NUM) {
      string t=(*store.begin()).second;
      if(visited.find( t )==visited.end())
      {
        BooleanFun target(seed.var_num());
        target.set_truth_table_hex(t);
        if( target.nonlinearity()>=241) {
          max_nonlinearity = target.nonlinearity();
          max_truth_table_hex=t;
          if(max_nonlinearity>240) {
            cout<<"round is "<<i<<endl;
            cout<< max_nonlinearity<<endl;
            cout<< max_truth_table_hex<<endl;
          }
        }
        bfs_queue.insert(*store.begin());
        visited.insert(t);
        store.erase(store.begin());
        j++;
      }
      else {
        store.erase(store.begin());
      }
    }
  }
  cout<<max_nonlinearity<<endl;
  cout<<max_truth_table_hex<<endl;
}

int main() {
  BooleanFun f(9);
  PermGroup PG(9);
  Permutation perm(9);
  //Permutation perm1(9);
  perm.set("2,3,4,1,6,7,8,5,9");
  //perm1.set("4,3,2,1,8,7,6,5,9");
  PG.add_generator(perm);
  //PG.add_generator(perm1);
  PG.compute_orbits();
  //cout<< PG.get_orbits_number()<<endl;
  //RotationSym RS(9);
  for (int run=0; run< 20; run++) {
    f.set_random_sym(PG.get_all_orbits());
    cout<< "run is "<<run<<endl;
    Best_fs(f,PG);
  }
  return 0;
}