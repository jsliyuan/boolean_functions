/* 
ReedMullerGener can generates all Boolean functions in n-variables with degree at most r.
*/

#include "reed_muller_generator.h"

#include <iostream>

using namespace std;

// Constructor with parameter (dimension), where n >= 1 and 0 <= r <= n.
ReedMullerGenerator::ReedMullerGenerator(int n, int r) {
  this->n = n;
  this->r = r;
  for (int x = 0; x < (1<<n); x ++) {
  	if (weight(x) <= r) {
  	  coefficients.push_back(x);
  	}
  }
  this->init();
}

 // Returns the number of one's in the binary representation of x.
int ReedMullerGenerator::weight(int x) {
  int sum = 0;
  while (x > 0) {
  	sum += x%2;
  	x = x/2;
  }
  return sum;
}

 // Initialize. Set the first Boolean function to zero.
 // You don't need to call it for the first time.
 void ReedMullerGenerator::init() {
   this->current = new BooleanFun(n, "0");
 }

// Returns the current Boolean function.
BooleanFun* ReedMullerGenerator::get_boolean_fun() const {
  return current;
}

// Generates the next homogenous Boolean function of degree r.
// Returns false if it hits the last one.
bool ReedMullerGenerator::next() {
  // Find the minimal index of a zero coefficient .
  int i = 0;
  while (i < coefficients.size() &&
  	     current->get_anf_coe(coefficients.at(i)) == 1) {
    i ++;
  }
  if (i == coefficients.size()) {
  	return false;
  }
  current->set_anf_coe(coefficients.at(i), 1);
  for (int j = 0; j < i; j ++) {
     current->set_anf_coe(coefficients.at(j), 0);
  }
  current->set_anf_coe_done();

  return true;
}
