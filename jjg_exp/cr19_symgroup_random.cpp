#include <iostream>
#include <time.h>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

#include "boolean_fun.h"
#include "permutation.h"
#include "sym_group.h"

using namespace std;

int main() {
  BooleanFun f(9);
  SymGroup SG(9);
  Permutation perm(9);
  perm.set("1,3,2,5,6,7,8,9,4");
  SG.set_generator(perm);
  SG.compute_orbits();
  // Initialize f at random
  
  for (int run=0; run< 20; run++) {
  f.set_random_sym(SG.get_all_orbits());
  set<string> store; 
  int max_value=0;
  string max_truth_table;
  // Local search from f
  for(int round=0; round<100000; round++) {
    vector<BooleanFun> ANF_of_fun;
    vector<int> walsh_of_fun; 
    for (int count=0; count < 104;count++) {
      vector<int> bin;
      bin=SG.get_full_orbit(count);

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
      
      ANF_of_fun.push_back(f_son);
      walsh_of_fun.push_back(f_son.cost());
    }
    auto minValue = min_element(walsh_of_fun.begin(),walsh_of_fun.end());
    int minPosition = minValue - walsh_of_fun.begin();
    bool process=true;
    int num_same=0;
    while(process) {
      string anf;
      anf=ANF_of_fun[minPosition].get_truth_table_hex();
      int flag=0;
      if(store.find(anf) != store.end()) {
        walsh_of_fun[minPosition]=2147483645;
        flag=1;
        num_same++;
      }
      if(flag==1 ) {
        minValue = min_element(walsh_of_fun.begin(),walsh_of_fun.end());
        minPosition = minValue - walsh_of_fun.begin();
      }
      else {
        process=false;
      }  
    }
    if(num_same<104) {
      store.insert(ANF_of_fun[minPosition].get_truth_table_hex());
      if(ANF_of_fun[minPosition].nonlinearity()>max_value) {
        max_value=ANF_of_fun[minPosition].nonlinearity();
        max_truth_table=ANF_of_fun[minPosition].get_truth_table_hex();
      }
      f=ANF_of_fun[minPosition];
    }
    else {
      cout<<"round is "<<round<<endl;
      break;
    }
  }
  cout<< "run is "<< run<<" nonlinearity: "<<max_value<<endl;
  cout<<max_truth_table<<endl;
  }
  return 0;
}
