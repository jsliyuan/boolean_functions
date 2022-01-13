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

  // Filter anf_str, igonring extrac spaces etc.
  string str;
  const string VALID_ANF_CHARS = "0123456789x+()";
  for (int i = 0; i < anf_str.size(); i ++) {
    if (VALID_ANF_CHARS.find(anf_str.at(i)) != std::string::npos) {
      str = str + anf_str.at(i); 
    }
  }
  anf_str = str;

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
      // Skip chars other than '0' - '9'
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

// Let this = 1 + this (over GF(2)). That is,
// take the negation.
void BooleanFun::negate() {
  for (int i = 0; i < (1<<n); i ++) {
    this->truth_table[i] = (this->truth_table[i] + 1) % 2;
  }

  this->anf[0] = (1 + this->anf[0]) % 2;
}

// Let this = this + f (over GF(2)).
// Returns false if #vars(f) != n.
bool BooleanFun::add(const BooleanFun& f) {
  if (n != f.var_num()) {
    return false;
  }

  for (int i = 0; i < (1<<n); i ++) {
    this->truth_table[i] = (this->truth_table[i] + f.value_dec(i)) % 2;
  }

  this->truth_table_to_anf();

  return true;
}

// Let this = this * f (over GF(2)).
// Returns false if #vars(f) != n.
bool BooleanFun::mult(const BooleanFun& f) {
  if (n != f.var_num()) {
    return false;
  }

  for (int i = 0; i < (1<<n); i ++) {
    this->truth_table[i] = this->truth_table[i] * f.value_dec(i);
  }

  this->truth_table_to_anf();

  return true;
}

// Apply affine transformation to this Boolean function, i.e.,
// f = f(T(x)) = f(Ax + b), where T(x) = Ax + b.
// Returns false if the dimension does not match.
// Both truth table and anf are updated.
bool BooleanFun::apply_affine_trans(const AffineTrans& trans) {
  if (this->n != trans.get_n()) {
    return false;
  }

  int* new_tt;
  new_tt = new int[1<<n];
  for (int i = 0; i < (1<<n); i ++) {
    int ti = trans.apply(i);
    new_tt[i] = this->truth_table[ti];
  }

  // Copy new_tt to truth_table
  for (int i = 0; i < (1<<n); i ++) {
    this->truth_table[i] = new_tt[i];
  }
  delete new_tt;

  // Updates ANF
  this->truth_table_to_anf();

  return true;
}
