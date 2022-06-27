#include "SymGroup.h"
#include "permutation.h"

#include <cstring>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <math.h>

using namespace std;

SymGroup::SymGroup(int n) {
  this->n = n;
  this->generators.clear();
  this->elements.clear();
  //initialize permuration 
  Permutation *identity= new Permutation(n);
  for(int i=1; i <= n ; i++) {
    (*identity).set(i,i);
  }
  elements.push_back(*identity);

  //initialize random seed
  srand(time(NULL));
}

// copy all data from g to this.
void SymGroup::copy_data(const SymGroup& SG) {
  this->n = SG.get_n();
  this->generators.clear();
  this->elements.clear();
  this->orbits.clear();
  for (const Permutation &it: SG.generators) {
    this->generators.push_back(it);
  }
  for (const Permutation &itt: SG.elements) {
    this->elements.push_back(itt);
  }
  for (const vector<int> &iter: SG.orbits) {
    this->orbits.push_back(iter);
  }
}

// Copy constructor.
SymGroup::SymGroup(const SymGroup& SG) {
  copy_data(SG);
}

// Assignment operator
SymGroup& SymGroup::operator=(const SymGroup& SG) {
  copy_data(SG);
  return *this;
}

void SymGroup::generate_all() {
  for (const Permutation& perm: this->generators) {
    this->elements.push_back(perm);
  }
  vector<Permutation> middle;
  middle=this->elements;
  while(middle.size()!=0) {
    vector<Permutation> middle1;
    for(const Permutation& perm1 : middle) {
      for(const Permutation& perm2 : this->elements) {
        Permutation *term= new Permutation(n);
        *term=perm1;
        (*term).left_mult(perm2);
        int flag=0;
        for(const Permutation& perm3: this->elements) {
          if(perm3==*term) {
            flag=1;
            break;
          }
        }
        if(flag==0) {
          this->elements.push_back(*term);
          middle1.push_back(*term);
        } 
      }  
    }
    middle=middle1;
  }
}

void SymGroup::compute_orbits() {
  generate_all();
  int count=0;
  for (int x=0;x<(1<<n);x++) {
    vector<int> bin;
    int num1;

    // transform decimal to binary
    int number=x;
    for (int t =n-1; t>-1; t--) {
      num1= (number>>t) ;
      number =number- num1*(pow(2,t));
      bin.push_back(num1);
    }

    vector <int>::iterator iter1;
    int flag=0;

    // whether the orbit of x has been found
    for(vector<vector<int> >::iterator it= this->orbits.begin();it!=this->orbits.end();it++) {
      iter1=find((*it).begin(),(*it).end(),x);
      if(iter1!=(*it).end()) {
        flag=1;
        break;
      } 
    }
    
    // if the orbit of x has not been found
    if(flag==0) {
      count++;
      int value=0;
      vector<int> bin1;
      
      for (vector<Permutation>:: iterator iter=this->elements.begin();iter!=this->elements.end();iter++) {
        const int* term=(*iter).get_perm();

        // permutation of x
        int* store;
        store=new int[n];
        for (int j=0;j<n;j++) {
          int pos=term[j]-1;
          store[j]=bin[pos];
        }
        //binary to decimal
        for(int p=0;p<n;p++) {
          value=value+(store[p]<<(n-1-p));
        }
        vector <int>::iterator itt;
        itt=find(bin1.begin(),bin1.end(),value);
        if (itt == bin1.end()) {
          // vector b is the orbit of i
          bin1.push_back(value);
        }
        value=0;
      }
      orbits.push_back(bin1);
    }
  }
}

// Returns the orbit of x .
std::vector<int> SymGroup::get_orbit(int x) {
  vector<int> cin;
  vector<int> din;
  int num;
  int value=0;
  // decimal to binary
  int number=x;
  for (int t =n-1; t>-1; t--) {
    num= (number>>t) ;
    number=number-num*(pow(2,t));
    cin.push_back(num);
  }
  for (vector<Permutation>:: iterator iter= this->elements.begin();iter!=this->elements.end();iter++) {
    const int* term=(*iter).get_perm();
    
    // permutation of x
    int* store;
    store=new int[n];
    for (int j=0;j<n;j++) {
      int pos=term[j]-1;
      store[j]=cin[pos];
    }
    //binary to decimal after permutation
    for(int j=0;j<n;j++) {
      value=value+(store[j]<<(n-1-j));
    }

    vector <int>::iterator itt;
    itt=find(din.begin(),din.end(),value);
    if (itt == din.end()) {
      // vector d is the orbit of i
      din.push_back(value);
    }
    value=0;
  }
  
  return din;
}

std::vector<int> SymGroup::get_full_orbit(int i) const {
  return this->orbits.at(i);
}

std::vector< std::vector<int> > SymGroup::get_all_orbits() {
  return this->orbits;
}

int SymGroup::get_orbits_number() const {
  return this->orbits.size();
}

int SymGroup::get_n() const {
  return this->n;
}

SymGroup::~SymGroup()
{
  this->generators.clear();
  this->elements.clear();
  this->orbits.clear();
}