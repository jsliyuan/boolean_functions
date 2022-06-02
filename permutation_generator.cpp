#include "permutation_generator.h"

#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <time.h>
#include <vector>

using namespace std;

Permutation::Permutation(int n) {
  this->n=n;
  perm = new int[n];
  for(int i=0; i<n; i++){
    perm[i]=i+1;
  }
  // initialize random seed
  srand(time(NULL));
}

bool Permutation::set(int* perm1) {
  for(int i=0;i<n;i++){
     perm[i]=perm1[i];
  }
  return true;
}

bool Permutation::set(string perm1) {
  stringstream text_stream(perm1);
  string item;
  int num=0;
  while (std::getline(text_stream, item, ',')) {
      perm[num]=stoi(item); 
      num++;
      if(num>n) {
        return false;
      }
  }
  return true;
}

bool Permutation::set(int idx, int val){
  if(idx<1||idx>n){
    return false;
  }
  if(val<1||val>n){
    return false;
  }
  perm[idx-1]=val;
  return true;
}

std::string Permutation::get_str(){
  string result ="";
  for (int i = 0; i < n; i ++) {
    if(i<n-1)
      result +=std::to_string(perm[i])+ ",";
    else 
      result+=std::to_string(perm[i]);
  }
  return result;
}

void Permutation::copy_data(const Permutation& perm1) {
  this->n = perm1.var_num();
  perm = new int[n];
  memcpy(perm, perm1.perm, n*sizeof(int));
}

// Assignment constructor
Permutation& Permutation::operator=(const Permutation& P) {
  if(perm){
    delete perm;
  }
  copy_data(P);
  return *this;
}

Permutation::Permutation(const Permutation& P){
  copy_data(P);
}

int Permutation::var_num() const {
  return n;
}

void Permutation::left_mult(const Permutation& perm1){
  int a;
  int* term;
  term=new int[n];
  for(int i=0;i<n;i++){
    term[i]=this->perm[i];
  }
  for(int j=0;j<n;j++){
      this->perm[j]=term[perm1.perm[j]-1];
  }
}

void Permutation::right_mult(const Permutation& perm1){
  int a;
  int* term;
  term=new int[n];
  for(int i=0;i<n;i++){
    term[i]=this->perm[i];
  }
  for(int j=0;j<n;j++){
      this->perm[j]=perm1.perm[term[j]-1];
  }
}

// BooleanFun destructor
Permutation::~Permutation()
{
  delete perm;
}

