#include "boolean_fun.h"
#include "boolean_fun_decoder.h"
#include "affine_trans.h"
#include "reed_muller_generator.h"
#include <assert.h>

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

bool vector_of_bfs_contasins_anf(string anf, vector<BooleanFun> term){
  vector<string> term1;
  for(int i=0;i<term.size();i++){
    term1.push_back((term.at(i)).get_anf());
  }
  if(std::find(term1.begin(), term1.end(), anf) != term1.end()){
    return true ;
  }
  else{
    return false;
  }
}

int main(){
  BooleanFunDecoder f1(3,"x1x2x3");
  assert(f1.second_order_nonlinearity_Fourquet_Tavernier()==1);
  vector<BooleanFun> term;
  term=f1.Fourquet_Tavernier_quadratic_list_decoding(2);
  assert(term.size()==8);
  assert(vector_of_bfs_contasins_anf("0",term));
  assert(vector_of_bfs_contasins_anf("x2x3",term));
  assert(vector_of_bfs_contasins_anf("x1x3",term));
  assert(vector_of_bfs_contasins_anf("x3+x2x3+x1x3",term));
  assert(vector_of_bfs_contasins_anf( "x1x2",term));
  assert(vector_of_bfs_contasins_anf("x2+x2x3+x1x2",term));
  assert(vector_of_bfs_contasins_anf( "x1+x1x3+x1x2",term));
  assert(vector_of_bfs_contasins_anf("1+x3+x2+x2x3+x1+x1x3+x1x2",term));

  vector<BooleanFun> term1;
  term1=f1.quadratic_list_decoding_brute_force(2);  
  assert(term1.size()==8);
  assert(vector_of_bfs_contasins_anf("0",term1));
  assert(vector_of_bfs_contasins_anf("x2x3",term1));
  assert(vector_of_bfs_contasins_anf("x1x3",term1));
  assert(vector_of_bfs_contasins_anf("x3+x2x3+x1x3",term1));
  assert(vector_of_bfs_contasins_anf("x1x2",term1));
  assert(vector_of_bfs_contasins_anf("x2+x2x3+x1x2",term1));
  assert(vector_of_bfs_contasins_anf("x1+x1x3+x1x2",term1));
  assert(vector_of_bfs_contasins_anf("1+x3+x2+x2x3+x1+x1x3+x1x2",term1));

  BooleanFunDecoder f2(3,"x1x2x3+x1+x2x3");
  assert(f2.nonlinearity(2)==1);
  assert(f2.second_order_nonlinearity_Fourquet_Tavernier()==1);
  vector<BooleanFun> term3;
  term3=f2.Fourquet_Tavernier_quadratic_list_decoding(2);
  assert(term3.size()==8);
  assert(vector_of_bfs_contasins_anf("x1",term3));
  assert(vector_of_bfs_contasins_anf("x2x3+x1",term3));
  assert(vector_of_bfs_contasins_anf("x3+x1+x1x3",term3));
  assert(vector_of_bfs_contasins_anf("x2x3+x1+x1x3",term3));
  assert(vector_of_bfs_contasins_anf("x2+x1+x1x2",term3));
  assert(vector_of_bfs_contasins_anf("x2x3+x1+x1x2",term3));
  assert(vector_of_bfs_contasins_anf( "1+x3+x2+x1x3+x1x2",term3));
  assert(vector_of_bfs_contasins_anf("x2x3+x1x3+x1x2",term3));

  vector<BooleanFun> term4;
  term4=f2.quadratic_list_decoding_brute_force(2);
  assert(term4.size()==8);
  assert(vector_of_bfs_contasins_anf("x1",term4));
  assert(vector_of_bfs_contasins_anf("x2x3+x1",term4));
  assert(vector_of_bfs_contasins_anf("x3+x1+x1x3",term4));
  assert(vector_of_bfs_contasins_anf( "x2x3+x1+x1x3",term4));
  assert(vector_of_bfs_contasins_anf("x2+x1+x1x2",term4));
  assert(vector_of_bfs_contasins_anf("x2x3+x1+x1x2",term4));
  assert(vector_of_bfs_contasins_anf("1+x3+x2+x1x3+x1x2",term4));
  assert(vector_of_bfs_contasins_anf("x2x3+x1x3+x1x2",term4));

  BooleanFunDecoder f3(4,"x1x2x3+x4");
  assert(f3.second_order_nonlinearity_Fourquet_Tavernier()==2);
  vector<BooleanFun> term5;
  term5=f3.Fourquet_Tavernier_quadratic_list_decoding(3);
  assert(term5.size()==8);
  assert(vector_of_bfs_contasins_anf("x4",term5));
  assert(vector_of_bfs_contasins_anf("x4+x2x3",term5));
  assert(vector_of_bfs_contasins_anf( "x4+x1x3",term5));
  assert(vector_of_bfs_contasins_anf("x4+x3+x2x3+x1x3",term5));
  assert(vector_of_bfs_contasins_anf("x4+x1x2",term5));
  assert(vector_of_bfs_contasins_anf( "x4+x2+x2x3+x1x2",term5));
  assert(vector_of_bfs_contasins_anf("x4+x1+x1x3+x1x2",term5));
  assert(vector_of_bfs_contasins_anf("1+x4+x3+x2+x2x3+x1+x1x3+x1x2",term5));

  vector<BooleanFun> term6;
  term6=f3.quadratic_list_decoding_brute_force(3);
  assert(term6.size()==8);
  assert(vector_of_bfs_contasins_anf("x4",term6));
  assert(vector_of_bfs_contasins_anf("x4+x2x3",term6));
  assert(vector_of_bfs_contasins_anf("x4+x1x3",term6));
  assert(vector_of_bfs_contasins_anf("x4+x3+x2x3+x1x3",term6));
  assert(vector_of_bfs_contasins_anf("x4+x1x2",term6));
  assert(vector_of_bfs_contasins_anf("x4+x2+x2x3+x1x2",term6));
  assert(vector_of_bfs_contasins_anf("x4+x1+x1x3+x1x2",term6));
  assert(vector_of_bfs_contasins_anf( "1+x4+x3+x2+x2x3+x1+x1x3+x1x2",term6));

  BooleanFunDecoder f4(4,"x1x2x4+x3x4");
  assert(f4.second_order_nonlinearity_Fourquet_Tavernier()==2);
  vector<BooleanFun> term7;
  term7=f4.Fourquet_Tavernier_quadratic_list_decoding(3);
  assert(term7.size()==8);
  assert(vector_of_bfs_contasins_anf("x3x4",term7));
  assert(vector_of_bfs_contasins_anf("x3x4+x2x4",term7));
  assert(vector_of_bfs_contasins_anf("x3x4+x1x4",term7));
  assert(vector_of_bfs_contasins_anf("x4+x3x4+x2x4+x1x4",term7));
  assert(vector_of_bfs_contasins_anf("x3x4+x1x2",term7));
  assert(vector_of_bfs_contasins_anf("x3x4+x2+x2x4+x1x2",term7));
  assert(vector_of_bfs_contasins_anf("x3x4+x1+x1x4+x1x2",term7));
  assert(vector_of_bfs_contasins_anf("1+x4+x3x4+x2+x2x4+x1+x1x4+x1x2",term7));

  vector<BooleanFun> term8;
  term8=f4.quadratic_list_decoding_brute_force(3);
  assert(term8.size()==8);
  assert(vector_of_bfs_contasins_anf("x3x4",term8));
  assert(vector_of_bfs_contasins_anf("x3x4+x2x4",term8));
  assert(vector_of_bfs_contasins_anf( "x3x4+x1x4",term8));
  assert(vector_of_bfs_contasins_anf("x4+x3x4+x2x4+x1x4",term8));
  assert(vector_of_bfs_contasins_anf( "x3x4+x1x2",term8));
  assert(vector_of_bfs_contasins_anf( "x3x4+x2+x2x4+x1x2",term8));
  assert(vector_of_bfs_contasins_anf("x3x4+x1+x1x4+x1x2",term8));
  assert(vector_of_bfs_contasins_anf("1+x4+x3x4+x2+x2x4+x1+x1x4+x1x2",term8));

  clock_t tStart = clock();
  BooleanFunDecoder f8_1(8);
  f8_1.set_truth_table_hex("02080292010B940B0104019EA45131AE20261343101685DA8A7346162F26BAEA");
  f8_1.set_truth_table_done();
  assert(f8_1.second_order_nonlinearity_Fourquet_Tavernier()==88);
  assert(f8_1.get_degree()==4);

  BooleanFunDecoder f8_2(8);
  f8_2.set_truth_table_hex("6BBCBCF2BFC2FD19BFCDC119CDD62697BCCEF2D5F11516A7C2E5D56B295B977C");
  f8_2.set_truth_table_done();
  assert(f8_2.second_order_nonlinearity_Fourquet_Tavernier()==88);
  assert(f8_2.get_degree()==4);

  BooleanFunDecoder f8_3(8);
  f8_3.set_truth_table_hex("7DF5ED65E8C64B56FA81C37B53BD657BDD998236E13F7D9F552E9FD75A776FBD");
  f8_3.set_truth_table_done();
  assert(f8_3.second_order_nonlinearity_Fourquet_Tavernier()==88);
  assert(f8_3.get_degree()==4);

  BooleanFunDecoder f8_4(8);
  f8_4.set_truth_table_hex("81363C783CD14DA33FD2D40641C5992D1ECCC51BF64211596017E25587A539D4");
  f8_4.set_truth_table_done();
  assert(f8_4.second_order_nonlinearity_Fourquet_Tavernier()==88);
  assert(f8_4.get_degree()==4);
  cout << "Done with nl2 for n = 8" << endl;
  cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " sec." << endl;
  
  /*
  // About 5mins.
  tStart = clock();
  cout << "Computing nl2 for some 9-variable function... (slow)" << endl;
  BooleanFun f9_1(9);
  f9_1.set_truth_table_hex("8884824287214E248774271744E2284D827E7748277E1E7B4142EE2127814BDE842271E47477428D2E787EEB12E171BE4214472DE8EB211E247D8B1E4DBEDEE1");
  f9_1.set_truth_table_done();
  assert(f9_1.second_order_nonlinearity_Fourquet_Tavernier()==196);
  assert(f9_1.get_degree()==4);
  cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " sec." << endl;
  */

  // About 80s.
  tStart = clock();
  cout << "Computing nl2 for some 9-variable function... (slow)" << endl;
  BooleanFunDecoder f9_2(9);
  f9_2.set_truth_table_hex("8222242E22412EE72228471828E1E77B242E27874771118D2181E114E8747DB4224E21E72878817B4E77711D111484D42E17881BE71D1444E78B7D447BD4B44E");
  f9_2.set_truth_table_done();
  assert(f9_2.second_order_nonlinearity_Fourquet_Tavernier()==196);
  assert(f9_2.get_degree()==3);
  cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << " sec." << endl;

  cout<<"Everything looks good. End of all tests." << endl;
  return 0;
}