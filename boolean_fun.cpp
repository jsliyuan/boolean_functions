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

// Returns the algebraic normal form of the Boolean function.
std::string BooleanFun::get_anf() const {
  std::string result = "";
  for (int i = 0; i < (1<<n); i ++) {
    if (anf[i] == 1) {
      if (result.size() > 0) {
        result += "+";
      }
      result += compose_term(i);
    }
  }
  if (result.size() == 0) {
    result = "0";
  }

  return result;
}

// Computes the mobius inversion of source[2^n], and writes
// the result into dest[2^n].
// dest[x] = XOR_{y <= x bitwise} source[y]
void BooleanFun::mobius_inversion(int* dest, int* source) {
  // Initialize
  for (int i = 0; i < (1<<n); i ++) {
    dest[i] = 0;
  }

  for (int j = 0; j < (1<<n); j ++) {
    if (source[j] == 0)
      continue;

    for (int i = 0; i < (1<<n); i ++) {
      // if j <= i bitwise, i.e., j | i = i
      if ((j | i) == i) {
        dest[i] = (dest[i] + source[j]) % 2;
      }
    }
  }
}

// Compute truth table from algebraic normal form.
void BooleanFun::anf_to_truth_table()
{
  this->mobius_inversion(truth_table, anf);
}

// Compute algebraic normal form from truth table.
void BooleanFun::truth_table_to_anf()
{
  this->mobius_inversion(anf, truth_table);
}

// Returns the decimal representation of the given term.
int BooleanFun::get_term(std::string term) const {
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

// The inverse of get_term()
std::string BooleanFun::compose_term(int dec) const {
  if (dec == 0) {
    return "1";
  }

  string term;
  for (int i = n; i >= 1; i --) {
    if (dec % 2 == 1) {
      term = "x" + std::to_string(i) + term;
    }
    dec = dec / 2;
  }
  return term;
}

// Returns the algebraic degree.
int BooleanFun::get_degree() const {
  int deg = 0;
  for (int i = 0; i < (1<<n); i ++) {
    if (anf[i] == 1 && weight(i) > deg) {
      deg = weight(i);
    }
  }
  return deg;
}

// BooleanFun destructor
BooleanFun::~BooleanFun()
{
  delete truth_table;
  delete anf;
}

// Returns the number of variables.
int BooleanFun::var_num() const {
  return n;
}

// Returns the base-2 weight of an integer， i.e., returns the
// number of one's in its binary representation.
int BooleanFun::weight(int x) const {
  int sum = 0;
  while (x > 0) {
    sum += x % 2;
    x = x/2;
  }

  return sum;
}

// Evaluate the Boolean function at a given point.
int BooleanFun::value(int num, ...) const {
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

// Evaluate the Boolean function at a given point,
// given the decimal representation of a point.
int BooleanFun::value_dec(int d) const {
  if (d < 0 || d >= (1<<n)) {
    return -1;
  }

  return truth_table[d];
}

// Checks if this Boolean function equals f.
bool BooleanFun::is_equal(const BooleanFun& f) const {
  if (f.var_num() != n) {
    return false;
  }

  for (int i = 0; i < (1<<f.var_num()); i ++) {
    if (f.value_dec(i) != truth_table[i]) {
      return false;
    }
  }
  return true;
}
