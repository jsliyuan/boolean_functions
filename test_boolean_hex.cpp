#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>
#include <vector>
#include <utility>

#include "boolean_fun.h"
#include "rotationsym.h"
#include "permutation.h"

using namespace std;

int main() {
  BooleanFun f9_find(9);
  f9_find.set_truth_table_hex("130A5089674581D62D7E7463C456E62C08F37EFD2F61391EA164732DB83C4CF150C1BB1E3EE9AEA20DEF39561AD346ADC95669203B5E4DA39E905EB164E5AB16");
  //f9_find.set_truth_table_done();
  cout<<f9_find.nonlinearity()<<endl;
  //cout<<f9_find.get_anf()<<endl;
 
  BooleanFun f9(9);
  f9.set_truth_table_hex("84345B7526DF2F364E02CBD6553706F331B9051DA09EF72D05324F5C34BE66A1ECF1EB47AD9B357E821715B6534D3EDA910D127B0776DB6CFEF8EAC1EC89A116");
  //f9.set_truth_table_done();
  cout<<f9.nonlinearity()<<endl;
  //cout<<f9.get_anf()<<endl;

  BooleanFun f9_1(9);
  f9_1.set_truth_table_hex("7A8D90B2C3449A496EF0EAC1EC9B21377CF8EB45AC89A5170116177C167E6EA1920D14B343659B5F100E167217578AF3031511BD426C7F0D7B8B809AD104D2C8");
  //f9.set_truth_table_done();
  cout<<f9_1.cost()<<endl;

  set<pair<int,BooleanFun> > store; 
  pair<int, BooleanFun> cur(f9_find.cost(),f9_find);
  store.insert(cur);
  pair<int, BooleanFun> cur1(f9.cost(),f9);
  store.insert(cur1);
  pair<int, BooleanFun> cur2(f9_1.cost(),f9_1);
  store.insert(cur2);

  for (const pair<int,BooleanFun>& perm:store) {
   cout<<perm.first<<" "<<perm.second.get_truth_table_hex()<<endl;
 }
 cout<<store.size();
  cout << endl<< "Everything looks good. End of all tests." << endl;
  return 0;
}
