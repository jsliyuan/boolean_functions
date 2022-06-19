#include "rotation_sym.h"
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

RotationSym::RotationSym(int n) {
  this->n = n;
  perms.clear();

  //initialize permuration 
  for (int i=1;i<n+1;i++) {
    int num=i;
    Permutation *p = new Permutation(n);
    for (int j=1;j<n+1;j++){
      if (num<n+1)
        (*p).set(j,num);
      else 
        (*p).set(j,num-n);     
      num++;
    }
    perms.push_back(*p);
    //cout<< p.get_str()<<endl;
  }

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
    for(vector<vector<int> >::iterator it=orbits.begin();it!=orbits.end();it++) {
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
      
      for (vector<Permutation>:: iterator iter=perms.begin();iter!=perms.end();iter++) {
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
          bin1.push_back(value);
        }
        value=0;
      }
      orbits.push_back(bin1);
    }
  }
  
  //initialize random seed
  srand(time(NULL));
}

// copy all data from g to this.
void RotationSym::copy_data(const RotationSym& RS) {
  this->n = RS.get_n();
  this->perms.clear();
  this->orbits.clear();
  for (const Permutation &it: RS.perms) {
    this->perms.push_back(it);
  }

  for (const vector<int> &itt: RS.orbits) {
    this->orbits.push_back(itt);
  }
}

// Copy constructor.
RotationSym::RotationSym(const RotationSym& RS) {
  copy_data(RS);
}

// Assignment operator
RotationSym& RotationSym::operator=(const RotationSym& RS) {
  copy_data(RS);
  return *this;
}

// Returns the orbit of x .
std::vector<int> RotationSym::get_orbit(int x) {
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

  for (vector<Permutation>:: iterator iter= this->perms.begin();iter!=this->perms.end();iter++) {
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

std::vector<int> RotationSym::get_full_orbit(int i) const {
  return orbits.at(i);
}

std::vector< std::vector<int> > RotationSym::get_all_orbits() {
  return this->orbits;
}

int RotationSym::get_orbits_number() const {
  return this->orbits.size();
}

int RotationSym::get_n() const {
  return this->n;
}

RotationSym::~RotationSym()
{
  this->perms.clear();
  this->orbits.clear();
}
