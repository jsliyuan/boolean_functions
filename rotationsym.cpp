#include "rotationsym.h"
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
  for (int i=1;i<n+1;i++)
  {
    int num=i;
    Permutation p(n);
    for (int j=1;j<n+1;j++){
      if (num<n+1)
        p.set(j,num);
      else 
        p.set(j,num-n);     
      num++;
    }
    perms.push_back(p);
    //cout<< p.get_str()<<endl;
  }

  int count=0;
  for (int i=0;i<(1<<n);i++) {
    vector<int> a;
    int num1;
    
    const int* term;

    // transform decimal to binary
    int number=i;
    for (int t =n-1; t>-1; t--) {
      num1= (number>>t) ;
      number =number- num1*(pow(2,t));
      a.push_back(num1);
    }
    // check the result 
    /*for (int z =0; z<n; z++) {
      cout<<a[z]<<" ";
    }
    cout<<endl;*/

    vector <int>::iterator iter;
    int flag=0;

    // whether the orbit of i has been found
    for(vector<vector<int> >::iterator it=orbits.begin();it!=orbits.end();it++) {
      iter=find((*it).begin(),(*it).end(),i);
      if(iter!=(*it).end()) {
        flag=1;
        break;
      } 
    }
    
    // if the orbit of i has not been found
    if(flag==0) {
      //cout<<",,,,,,"<<endl;
      count++;
      int value=0;
      vector<int> b;
      int* store;
      for (vector<Permutation>:: iterator iter=perms.begin();iter!=perms.end();iter++) {
        term= (*iter).get_perm();
        /*for (int j=0;j<n;j++) {
          cout<<term[j]<<" ";
        }*/
        //cout<<(*iter).get_str()<<endl;

        // permutation of i
        for (int j=0;j<n;j++) {
          int pos=term[j]-1;
          store[j]=a[pos];
        }
        
        /*for (int m=0;m<n;m++) {
          cout<<store[m]<<" ";
        }
        cout<<endl;*/

        //binary to decimal
        for(int p=0;p<n;p++) {
          value=value+(store[p]<<(n-1-p));
        }
        //cout<<"value is: "<<value<<endl;

        vector <int>::iterator itt;
        itt=find(b.begin(),b.end(),value);
        if (itt == b.end()) {
          // vector b is the orbit of i
          b.push_back(value);
        }
        value=0;
      }
      orbits.push_back(b);
      //cout<<" "<<b.size()<<" ";
    }
  }
  cout<<"the number of orbits is "<<count<<endl; 
  
  // initialize random seed
  //srand(time(NULL));
}

// copy all data from g to this.
void RotationSym::copy_data(const RotationSym& RS) {
  this->n = RS.get_n();
  this->perms.clear();
  for (const Permutation &it: RS.perms) {
    this->perms.push_back(it);
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

// Returns the orbit of i .
vector<int> RotationSym::get_orbit(int i) {
  vector<int> c;
  vector<int> d;
  int num;
  int value=0;
  const int* term;
  int* store;
  // decimal to binary
  int number=i;
  for (int t =n-1; t>-1; t--) {
    num= (number>>t) ;
    number=number-num*(pow(2,t));
    c.push_back(num);
  }
  /*for (int t =0; t<n; t++) {
    cout<<c[t]<<" ";
  }
  cout<<endl;*/

  for (vector<Permutation>:: iterator iter=perms.begin();iter!=perms.end();iter++) {
    term= (*iter).get_perm();
    // permutation of i
    for (int j=0;j<n;j++) {
      int pos=term[j]-1;
      store[j]=c[pos];
    }

    //binary to decimal after permutation
    for(int j=0;j<n;j++) {
      value=value+(store[j]<<(n-1-j));
    }

    vector <int>::iterator itt;
    itt=find(d.begin(),d.end(),value);
    if (itt == d.end()) {
      // vector d is the orbit of i
      d.push_back(value);
    }
    value=0;
  }
  return d;
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