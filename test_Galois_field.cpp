#include"Galois_field.h"

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <unordered_set>

using namespace std;

void print(int* v, int n) {
    for (int i = 0; i < n; i++) {
        cout << v[i] << "  ";
    }
    cout << endl;
}

int main(){
  srand((int)time(NULL));
  int n=10;
  Field tf(n);
  int* te=new int[n];
  
  //Test btoi,itob
  itob(10,te,n);
  assert(btoi(te,n)==10);
  itob(0,te,n);
  assert(btoi(te,n)==0);
  itob(1,te,n);
  assert(btoi(te,n)==1);

  //Test add
  assert(tf.add(3,3)==0);
  assert(tf.add(5,2)==7);
  assert(tf.add(1,3)==2);
  assert(tf.add(8,3)==11);

  //Test selfMul,mul
  assert(tf.mul(0,10)==0);
  assert(tf.mul(1,10)==10);
  
  //Test ord
  for (int i=1;i<=tf.m;i++){
    assert(tf.m%tf.ord(i)==0);
  }

  //Test Irrpoly,Pri
  for (int i=2;i<=10;i++){
    Field f(i);
    //printf("%d : %d  ;  ", i, f.irrp);
    //print(f.irrpb, i + 1);
    //cout<<i<<": "<<f.al<<endl;
    assert(f.ord(f.al)==f.m);
  }

  //Test mulGroup
  for (int i=2;i<11;i++){
    Field f(i);
    int* mg=f.mg;
    unordered_set<int> s;
    for (int j=0;j<f.m;j++){
      assert(s.find(mg[j])==s.end());
      s.insert(mg[j]);
    }
    assert(s.size()==f.m);
  }
  
  // Test TruthToUn,UnToTruth
  int* truth=new int[1<<n];
  int* un=new int[1<<n];
  int* test_truth=new int[1<<n];
  for (int k = 0; k < 20; k++) {
    for (int i=0;i<1<<n;i++){
        truth[i]=rand()%2;
        test_truth[i]=0;
    }
    TruthToUn(truth,un,&tf);
    //print(un,f.m+1);
    assert(isBoolean(un,&tf)==true);
    UnToTruth(un, test_truth, &tf); 
    for (int i=0;i<1<<n;i++){
    //cout<<truth[i]<<" "<<test_truth[i]<<endl;
        assert(truth[i]==test_truth[i]);
    }
    printf("第%d个例子已通过!\n", k+1);
  }
  delete truth;delete un;delete test_truth;

  //Test tr
  int k;
  for (int i=0;i<10;i++){
    k=tf.tr(rand()%(tf.m+1));
    assert(k==0||k==1);
  }
  
  //GC
  delete te;
}