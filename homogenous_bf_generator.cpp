#include "homogenous_bf_generator.h"

#include <iostream>

using namespace std;

// Constructor with parameter (dimension), where n >= 1 and 0 <= r <= n.
HomogenousBfGenerator::HomogenousBfGenerator(int n, int r) {
  this->n = n;
  this->r = r;
  for (int x = 0; x < (1<<n); x ++) {
  	if (weight(x) == r) {
  	  coefficients.push_back(x);
  	}
  }
  this->init();
}

 // Returns the number of one's in the binary representation of x.
int HomogenousBfGenerator::weight(int x) {
  int sum = 0;
  while (x > 0) {
  	sum += x%2;
  	x = x/2;
  }
  return sum;
}

 // Initialize. Set the first Boolean function to zero.
 // You don't need to call it for the first time.
 void HomogenousBfGenerator::init() {
   this->current = new BooleanFun(n, "0");
 }

// Returns the current Boolean function.
BooleanFun* HomogenousBfGenerator::get_boolean_fun() const {
  return current;
}

// Generates the next homogenous Boolean function of degree r.
// Returns false if it hits the last one.
bool HomogenousBfGenerator::next() {
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
