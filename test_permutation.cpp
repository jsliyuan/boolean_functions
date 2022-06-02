#include <iostream>
#include <time.h>
#include <set>
#include <assert.h>

#include "permutation_generator.h"

using namespace std;

int main() {
  Permutation p(6);
  assert(p.get_str()=="1,2,3,4,5,6");
  p.set("3,4,5,6,1,2");
  assert(p.get_str()=="3,4,5,6,1,2");
  Permutation p1(6);
  p1=p;
  assert(p1.get_str()=="3,4,5,6,1,2");
  p1.left_mult(p);
  assert(p1.get_str()=="5,6,1,2,3,4");
  p.left_mult(p1);
  assert(p.get_str()=="1,2,3,4,5,6");
  p1.right_mult(p);
  assert(p1.get_str()=="5,6,1,2,3,4");
  p1.left_mult(p);
  assert(p1.get_str()=="5,6,1,2,3,4");

  Permutation p_9(9);
  p_9.set(1,2);
  p_9.set(2,3);
  p_9.set(3,4);
  p_9.set(4,5);
  p_9.set(5,6);
  p_9.set(6,7);
  p_9.set(7,8);
  p_9.set(8,9);
  p_9.set(9,1);
  assert(p_9.get_str()=="2,3,4,5,6,7,8,9,1");

  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}
