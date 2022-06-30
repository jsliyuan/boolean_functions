#include "homogenous_bf_generator.h"

#include <iostream>
#include <assert.h>
#include <cassert>

using namespace std;

int main() {
  HomogenousBfGenerator gen60(6,0);
  assert(gen60.get_boolean_fun()->get_anf() == "0");
  assert(gen60.next());
  assert(gen60.get_boolean_fun()->get_anf() == "1");
  assert(gen60.next() == false);
  cout << "End of test for gen60(6, 0)" << endl;

  HomogenousBfGenerator gen61(6,1);
  int total = 1;
  while (gen61.next()) {
  	total ++;
  	assert(gen61.get_boolean_fun()->get_degree() == 1);
  }
  assert(total == (1<<6));
  cout << "End of test for gen61(6, 1)" << endl;

  HomogenousBfGenerator gen62(6,2);
  total = 1;
  while (gen62.next()) {
  	total ++;
  	assert(gen62.get_boolean_fun()->get_degree() == 2);
  }
  assert(total == (1<<15));
  cout << "End of test for gen62(6, 2)" << endl;

  HomogenousBfGenerator gen63(6,3);
  total = 1;
  while (gen63.next()) {
  	total ++;
  	//cout << gen63.get_boolean_fun()->get_anf() << endl;
  	assert(gen63.get_boolean_fun()->get_degree() == 3);
  }
  assert(total == (1<<20));
  cout << "End of test for gen63(6, 3)" << endl;

  HomogenousBfGenerator gen66(6,6);
  assert(gen66.get_boolean_fun()->get_anf() == "0");
  assert(gen66.next());
  assert(gen66.get_boolean_fun()->get_anf() == "x1x2x3x4x5x6");
  assert(gen66.next() == false);
  cout << "End of test for gen66(6, 6)" << endl;

  return 1;
}