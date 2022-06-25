#include <iostream>
#include <time.h>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

#include "boolean_fun.h"
#include "permutation.h"
#include "rotationsym.h"

using namespace std;

int main() {
  BooleanFun f(9);
  RotationSym f1(9);
  // Initialize f at random
  set<string> store; 
  for (int run=0; run< 10; run++) {
  f.set_random_sym(f1.get_all_orbits());
  
  // Local search from f
  for(int round=0; round<100000; round++) {
    vector<BooleanFun> ANF_of_fun;
    vector<int> walsh_of_fun; 
    for (int count=0; count < 60;count++) {
      vector<int> bin;
      bin=f1.get_full_orbit(count);

      BooleanFun f_son(9);
      f_son=f;

      int* term;
      term=f_son.truth_table;

      //int pos=rand()%(bin.size());
      if(term[bin[0]]==1){
        f_son.set_truth_table_orbit(bin,0);
        f_son.set_truth_table_done();
      }
      else {
        f_son.set_truth_table_orbit(bin,1);
        f_son.set_truth_table_done();
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
    if(num_same<60) {
      store.insert(ANF_of_fun[minPosition].get_truth_table_hex());
      f=ANF_of_fun[minPosition];
    }
    else {
      cout<<"round is "<<round<<endl;
      break;
    }
  }
  }
  vector<int> value_nonlinearity;
  for (const string& anf1 : store) {
    BooleanFun g(9);
    g.set_truth_table_hex(anf1);
    g.set_truth_table_done();
    value_nonlinearity.push_back(g.nonlinearity());
  }
  auto Max_nonlinearity=max_element(value_nonlinearity.begin(),value_nonlinearity.end());
  int maxpos=Max_nonlinearity - value_nonlinearity.begin();
  set<string>::iterator iter1;
  iter1 = store.begin();
  for(int j=1; j<=maxpos;j++) {
    iter1++;
  }
  cout<<*iter1<<endl;
  cout<<*Max_nonlinearity<<endl;
  return 0;
}
