#include"Galois_field.h"

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <unordered_set>

using namespace std;

void print(int* v, int n) {
    cout << "\tthis->irrpb = new int[" << n << "]{";
    for (int i = 0; i < n; i++) {
        cout << v[i] << ",";
    }
    cout << "};" << endl;
}

int main() {
 
  srand((int)time(NULL));
  int n=10;
  Field tf(n);
  int* te=new int[n];

  //Test btoi,itob
  tf.itob(10,te,n);
  assert(tf.btoi(te,n)==10);
  tf.itob(0,te,n);
  assert(tf.btoi(te,n)==0);
  tf.itob(1,te,n);
  assert(tf.btoi(te,n)==1);
  cout<<"End of test for int to binary & int to binary "<<endl;

  //Test add
  assert(tf.add(3,3)==0);
  assert(tf.add(5,2)==7);
  assert(tf.add(1,3)==2);
  assert(tf.add(8,3)==11);
  cout<<"End of test for addition "<<endl;

  //Test selfMul,mul
  assert(tf.mul(0,10)==0);
  assert(tf.mul(1,10)==10);
  cout<<"End of test for multiplication "<<endl;

  //Test ord
  for (int i=1;i<=tf.get_order();i++){
      int order_i = tf.ord(i);
      assert(tf.get_order() % order_i == 0);
      assert(tf.selfMul(i, order_i) == 1);
  }
  cout<<"End of test for order"<<endl;

  //Test sub
  for (int i = 0; i < 20; i++) {
      int a = rand() % (tf.get_order() + 1);
      int b = rand() % (tf.get_order() + 1);
      assert(tf.sub(tf.selfMul(a, 2), tf.selfMul(b, 2)) == tf.mul(tf.add(a, b), tf.sub(a, b)));
  }
  cout << "End of test of sub" << endl;

  //Test inv,div
  for (int i = 0; i < 20; i++) {
      int a = rand() % (tf.get_order() + 1);
      int b = rand() % (tf.get_order() + 1);
      assert(tf.inv(tf.mul(a, b)) == tf.mul(tf.inv(a), tf.inv(b)));
      assert(tf.mul(a, tf.inv(b)) == tf.div(a, b));
  }
  cout << "End of test for inv & div" << endl;

  //Test Irrpoly,Pri
  for (int i=2;i<=12;i++){
    Field f(i);
    assert(f.ord(f.get_root())==f.get_order());
    cout << i<< " Pri true" << endl;
  }
  cout<<"End of test for irreducible polynomial in GF(2) with degree n "<<endl;

  //Test mulGroup
  for (int i=2;i<=12;i++){
    Field f(i);
    const int* mg=f.get_root_list();
    unordered_set<int> s;
    for (int j=0;j<f.get_order();j++){
      assert(s.find(mg[j])==s.end());
      s.insert(mg[j]);
    }
    assert(s.size()==f.get_order());
  }
  cout<<"End of test for multiple group of F2^n "<<endl;

  // Test TruthToUn,UnToTruth
  int* truth=new int[1<<n];
  int* un=new int[1<<n];
  int* test_truth=new int[1<<n];
  for (int k = 0; k < 10; k++) {
    for (int i=0;i<1<<n;i++){
        truth[i]=rand()%2;
        test_truth[i]=0;
    }
    tf.TruthToUn(truth,un);
    cout << 1 << endl;
    //print(un,f.m+1);
    assert(tf.isBoolean(un)==true);
    cout << 2 << endl;
    tf.UnToTruth(un, test_truth);
    cout << 3 << endl;
    for (int i=0;i<1<<n;i++){
    //cout<<truth[i]<<" "<<test_truth[i]<<endl;
        assert(truth[i]==test_truth[i]);
    }
    cout << k << "th pass!" << endl;
  }
  delete[] truth;
  delete[] un;
  delete[] test_truth;
  cout<<"End of test for TruthToUn and UnToTruth"<<endl;

  //Test tr
  int k;
  for (int i=0;i<10;i++){
    k=tf.tr1(rand()%(tf.get_order()+1));
    assert(k==0||k==1);
  }

  //GC
  delete te;
 

    cout << "End of test. Everything looks good." << endl;
    return 0;

}
