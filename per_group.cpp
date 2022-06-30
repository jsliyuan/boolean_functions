#include "per_group.h"
#include "permutation.h"

#include <cstring>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <set>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <math.h>

using namespace std;

PermGroup::PermGroup(int n) {
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
void PermGroup::copy_data(const PermGroup& PG) {
  this->n = PG.get_n();
  this->generators.clear();
  this->elements.clear();
  this->orbits.clear();
  for (const Permutation &it: PG.generators) {
    this->generators.push_back(it);
  }
  for (const Permutation &itt: PG.elements) {
    this->elements.push_back(itt);
  }
  for (const vector<int> &iter: PG.orbits) {
    this->orbits.push_back(iter);
  }
}

// Copy constructor.
PermGroup::PermGroup(const PermGroup& PG) {
  copy_data(PG);
}

// Assignment operator
PermGroup& PermGroup::operator=(const PermGroup& PG) {
  copy_data(PG);
  return *this;
}

void PermGroup::generate_all() {
  for (vector<Permutation>::iterator it= this->generators.begin();it!=this->generators.end();it++) {
    elements.push_back(*it);
  }
  vector<Permutation> queue;
  queue=this->elements;
  int head=0,tail=queue.size()-1; 
  while(head<=tail) {
    Permutation *cur=new Permutation(n);
    *cur=queue.at(head);
    vector<Permutation> term;
    term=this->elements;
    for( vector<Permutation>::iterator it= term.begin();it!=term.end();it++) {
      Permutation *new_element=new Permutation(n);
      *new_element=*cur;
      (*new_element).left_mult(*it);
      vector<Permutation>::iterator iter;
      iter=find(this->elements.begin(),this->elements.end(),*new_element);
      if(iter==this->elements.end()) {
        this->elements.push_back(*new_element);
        queue.push_back(*new_element);
        tail++;
      }
    } 
    head++;
  }  
}

void PermGroup::compute_orbits() {
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
std::vector<int> PermGroup::get_orbit(int x) {
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

std::vector<int> PermGroup::get_full_orbit(int i) const {
  return this->orbits.at(i);
}

std::vector< std::vector<int> > PermGroup::get_all_orbits() {
  return this->orbits;
}

int PermGroup::get_orbits_number() const {
  return this->orbits.size();
}

int PermGroup::get_n() const {
  return this->n;
}

PermGroup::~PermGroup()
{
  this->generators.clear();
  this->elements.clear();
  this->orbits.clear();
}
