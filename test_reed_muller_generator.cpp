#include "reed_muller_generator.h"

#include <iostream>
#include <assert.h>
#include <cassert>

using namespace std;

int main() {
  ReedMullerGenerator rm40(4,0);
  assert(rm40.get_boolean_fun()->get_anf() == "0");
  assert(rm40.next());
  assert(rm40.get_boolean_fun()->get_anf() == "1");
  assert(rm40.next() == false);
  cout << "End of test for rm40(4, 0)" << endl;

  ReedMullerGenerator rm41(4,1);
  long long total = 1;
  while (rm41.next()) {
  	total ++;
  	assert(rm41.get_boolean_fun()->get_degree() <= 1);
  }
  assert(total == (1<<5) );
  cout << "End of test for rm41(4, 1)" << endl;

  ReedMullerGenerator rm42(4,2);
 total = 1;
  while (rm42.next()) {
  	total ++;
  	assert(rm42.get_boolean_fun()->get_degree() <= 2);
  }
  assert(total == (1<<11) );
  cout << "End of test for rm42(4, 2)" << endl;

  ReedMullerGenerator rm43(4,3);
  total = 1;
  while (rm43.next()) {
  	total ++;
  	assert(rm43.get_boolean_fun()->get_degree() <= 3);
  }
  assert(total == (1<<15) );
  cout << "End of test for rm43(4, 3)" << endl;

  ReedMullerGenerator rm44(4,4);
  total = 1;
  while (rm44.next()) {
  	total ++;
  	assert(rm44.get_boolean_fun()->get_degree() <= 4);
  }
  assert(total == (1<<16) );
  cout << "End of test for rm44(4, 4)" << endl;

  ReedMullerGenerator rm51(5,1);
  total = 1;
  while (rm51.next()) {
  	total ++;
  	assert(rm51.get_boolean_fun()->get_degree() <= 1);
  }
  assert(total == (1<<6) );
  cout << "End of test for rm51(5, 1)" << endl;

  ReedMullerGenerator rm52(5,2);
 total = 1;
  while (rm52.next()) {
  	total ++;
  	assert(rm52.get_boolean_fun()->get_degree() <= 2);
  }
  assert(total == (1<<16));
  cout << "End of test for rm52(5, 2)" << endl;

  ReedMullerGenerator rm60(6,0);
  assert(rm60.get_boolean_fun()->get_anf() == "0");
  assert(rm60.next());
  assert(rm60.get_boolean_fun()->get_anf() == "1");
  assert(rm60.next() == false);
  cout << "End of test for rm60(6, 0)" << endl;

  ReedMullerGenerator rm61(6,1);
  total = 1;
  while (rm61.next()) {
  	total ++;
  	assert(rm61.get_boolean_fun()->get_degree() <= 1);
  }
  assert(total == (1<<7) );
  cout << "End of test for rm61(6, 1)" << endl;

  ReedMullerGenerator rm62(6,2);
  total = 1;
  while (rm62.next()) {
  	total ++;
  	assert(rm62.get_boolean_fun()->get_degree() <= 2);
  }
  assert(total == (1<<22) );
  cout << "End of test for rm62(6, 2)" << endl;

  ReedMullerGenerator rm70(7,0);
  assert(rm70.get_boolean_fun()->get_anf() == "0");
  assert(rm70.next());
  assert(rm70.get_boolean_fun()->get_anf() == "1");
  assert(rm70.next() == false);
  cout << "End of test for rm70(7, 0)" << endl;

  ReedMullerGenerator rm71(7,1);
  total=1;
  while (rm71.next()) {
  	total ++;
  	assert(rm71.get_boolean_fun()->get_degree() <= 1);
  }
  assert(total == (1<<8) );
  cout << "End of test for rm71(7, 1)" << endl;

  

  return 1;
}