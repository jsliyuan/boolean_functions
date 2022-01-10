#include "boolean_fun.h"

#include <iostream>

using namespace std;

// BooleanFun constructor with parameter (number of variables)
BooleanFun::BooleanFun(int n)
{
  this->n = n;
  truth_table = new int[1<<n];
  anf = new int[1<<n];
}

// Constructor with parameters, where n is the number
// of variables, and anf_str is the algebraic normal form.
// For example,
//   anf = "x1x2+x3+1"
BooleanFun::BooleanFun(int n, string anf_str)
{
  this->n = n;
  truth_table = new int[1<<n];
  anf = new int[1<<n];

  string term;
  // Split anf by '+'; for each term, set the coefficient to +1.
  int i = 0;
  while (i <= anf_str.size()) {
    if (i == anf_str.size() || anf_str.at(i) == '+') {
      // Constant term "0" or "1"
      if (term == "1") {
        anf[0] = (anf[0] + 1) % 2;
      }
      if (term.size() > 1) {
        int d = get_term(term);
        anf[d] = (anf[d] + 1) % 2;
      }
      term = "";
    }  else {
      term += anf_str.at(i);
    }

    i ++;
  }

  // Compute truth_table using anf
  anf_to_truth_table();
}

// Compute truth table from algebraic normal form.
void BooleanFun::anf_to_truth_table()
{
  for (int j = 0; j < (1<<n); j ++) {
    if (anf[j] == 0)
      continue;

    for (int i = 0; i < (1<<n); i ++) {
      // if j <= i bitwise, i.e., j | i = i
      if ((j | i) == i) {
        truth_table[i] = (truth_table[i] + anf[j]) % 2;
      }
    }
  }
}

// Returns the decimal representation of the given term.
int BooleanFun::get_term(std::string term) {
  int binary[n];
  for (int i = 0; i < n; i ++)
    binary[i] = 0;

  int i = 0;
  int v = 0;
  term = term + "x";
  while (i < term.size()) {
    if (i == term.size() || term.at(i) == 'x') {
      if (i > 0) {
        binary[v-1] = 1;
      }
      v = 0;
    } else {
      v = v*10 + term.at(i) - '0';
    }
    i ++;
  }

  // Convert binary[] to a decimal number.
  int result = 0;
  for (i = 0; i < n; i ++) {
    result = result*2 + binary[i];
  }
  return result;
}

// BooleanFun destructor
BooleanFun::~BooleanFun()
{
  delete truth_table;
  delete anf;
}

// Returns the number of variables.
int BooleanFun::var_num() {
  return n;
}

// Evaluate the Boolean function at a given point.
int BooleanFun::value(int num, ...) {
  if (num != n) {
    return -1;
  }
  va_list valist;

  int dec = 0;
  va_start(valist, num);
  for (int i = 0;  i < num; i ++) {
    dec = dec*2 + va_arg(valist, int);
  }
  va_end(valist);
  return truth_table[dec];
}
