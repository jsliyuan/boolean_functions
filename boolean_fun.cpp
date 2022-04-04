#include "boolean_fun.h"

#include <iostream>
#include <vector>

using namespace std;

// BooleanFun constructor with parameter (number of variables)
BooleanFun::BooleanFun(int n)
{
  this->n = n;
  truth_table = new int[1<<n];
  anf = new int[1<<n];
  for (int i = 0; i < (1<<n); i ++) {
    truth_table[i] = 0;
    anf[i] = 0;
  }
  degree = 0;
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
  for (int i = 0; i < (1<<n); i ++) {
    truth_table[i] = 0;
    anf[i] = 0;
  }

  this->set_anf(anf_str);

  // Compute truth_table using anf
  anf_to_truth_table();
  compute_degree();
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

// Returns anf[d], where d is in [0, 2^n-1].
int BooleanFun::get_anf_coe(int d) const {
  if (d < 0 || d >= (1<<n)) {
    return -1;
  }

  return anf[d];
}

// Set the truth_table[x] to v, where
// x is in [0, 2^n-1], and v is 0 or 1.
// Returns false if x or v is out of range.
bool BooleanFun::set_truth_table(int x, int v) {
  if (x < 0 || x >= (1<<n)) {
    return false;
  }
  if (v < 0 || v > 1) {
    return false;
  }

  truth_table[x] = v;
  return true;
}

// After setting the truth table, call this function.
// The degree and ANF will be computed then.
void BooleanFun::set_truth_table_done() {
  this->truth_table_to_anf();
  this->compute_degree();
}

// Resets the ANF.
// Both truth table and anf are modified.
// Returns false if anf_str is invalid.
bool BooleanFun::set_anf(std::string anf_str) {
  // Clears the orginal anf.
  for (int i = 0; i < (1<<n); i ++) {
    anf[i] = 0;
  }

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
  compute_degree();

  return true;
}

// Sets the coefficient d of the ANF to constant c,
// where d is in [0, 2^n-1], and c is 0 or 1.
bool BooleanFun::set_anf_coe(int d, int c) {
  if (d < 0 || d >= (1 << n)) {
    return false;
  }
  if (c < 0 || c > 1) {
    return false;
  }
  anf[d] = c;

  return true;
}

void BooleanFun::set_anf_coe_done() {
  // Compute truth_table using anf
  anf_to_truth_table();
  compute_degree();
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

// Computes this->degree.
void BooleanFun::compute_degree() {
  int deg = 0;
  for (int i = 0; i < (1<<n); i ++) {
    if (anf[i] == 1 && weight(i) > deg) {
      deg = weight(i);
    }
  }
  this->degree = deg;
}

// Returns the algebraic degree.
int BooleanFun::get_degree() const {
  return this->degree;
}

// Returns the subfunction in n-1 variables by setting
// x_n to constant c.
BooleanFun BooleanFun::sub_function(int c) const {
  BooleanFun sub(n-1);
  for (int x = 0; x < (1<<n); x ++) {
    int xn = x % 2;
    if (xn == c) {
      sub.set_truth_table(x / 2, truth_table[x]);
    }
  }
  sub.set_truth_table_done();
  return sub;
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
    this->truth_table[i] = (this->truth_table[i] + f.truth_table[i]) % 2;
  }

  this->truth_table_to_anf();
  this->compute_degree();

  return true;
}

// Let this = this * f (over GF(2)).
// Returns false if #vars(f) != n.
bool BooleanFun::mult(const BooleanFun& f) {
  if (n != f.var_num()) {
    return false;
  }

  for (int i = 0; i < (1<<n); i ++) {
    this->truth_table[i] = this->truth_table[i] * f.truth_table[i];
  }

  this->truth_table_to_anf();
  this->compute_degree();

  return true;
}

// Trim all monomials whose degree is less than deg_upper.
void BooleanFun::trim_degree_below(int deg_upper) {
  bool modified = false;

  for (int i = 0; i < (1<<n); i ++) {
    if (this->weight(i) < deg_upper && anf[i] > 0) {
      anf[i] = 0;
      modified = true;
    }
  }
  if (modified) {
    this->anf_to_truth_table();
    if (deg_upper > this->degree) {
      this->degree = 0;
    }
  }
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

// Returns the Hamming distance between two Boolean functions.
// If their #variables do not match, return -1.
int BooleanFun::dist(const BooleanFun& f) const {
  if (this->n != f.var_num()) {
    return -1;
  }

  int total = 0;
  for (int i = 0; i < (1<<n); i ++) {
    if (f.value_dec(i) != truth_table[i]) {
      total ++;
    }
  }
  return total;
}

// Returns true if this Boolean function is homogeneous
// as a polynomial over GF(2).
bool BooleanFun::is_homogenous() const {
  for (int i = 0; i < (1 << n); i ++) {
    if (anf[i] == 1 && weight(i) != degree)
      return false;
  }
  return true;
}

// Compute the Walsh transform on w, where w is in [0, 2^n-1]
// (w1, w2, ..., wn) -> d(w) := w_1*2^{n-1}+w_2*2^{n-2}+...+w_n.
// W(w) = sum_{x} (-1)^(f(x) + w*x)
int BooleanFun::walsh_transform(int w) const {
  int sum = 0;
  for (int i = 0; i < (1 << n); i ++) {
    int parity = truth_table[i] + inner_product(i, w);
    if (parity % 2 == 0) {
      sum += 1;
    } else {
      sum -= 1;
    }
  }

  return sum;
}

// Compute the inner product of x and y, viewed as vector {0,1}^n
int BooleanFun::inner_product(int x, int y) const {
  int prod = x & y;
  int sum = 0;
  while (prod > 0) {
    sum += prod % 2;
    prod = prod / 2;
  }

  return sum;
}

// Returns the first-order nonlinearity, which is
// 2^{n-1} - max_w |walsh_transform(w)| / 2.
int BooleanFun::nonlinearity() const {
  int max_w = 0;
  int sum[(1<<n)];
  for (int w = 0; w < (1 << n); w ++) {
    sum[w] = 0;
  }

  int parity;
  int val;
  for (int i = 0; i < (1 << n); i ++) {
    int val = truth_table[i];
    for (int w = 0; w < (1 << n); w ++) {
      parity = val + inner_product(i, w);
      if (parity % 2 == 0) {
        sum[w] += 1;
      } else {
        sum[w] -= 1;
      }
    }
  }

  for (int w = 0; w < (1 << n); w ++) {
    if (sum[w] > max_w) {
      max_w = sum[w];
    }
    if (-sum[w] > max_w) {
      max_w = -sum[w];
    }
  }

  return (1<<(n-1)) - max_w/2;
}

// Returns the rth-order nonlinearity.
// Cut the search if existing value is > upper_bound
int BooleanFun::nonlinearity(int r, int upper_bound) const {
  if (r >= degree) {
    return 0;
  }
  if (r == 1) {
    return nonlinearity();
  }

  // Find all x in [0, 2^(n-1)-1] with weight r.
  vector<int> deg_r_x;
  for (int i = 0; i < (1<<(n-1)); i ++) {
    if (weight(i) == r) {
      deg_r_x.push_back(i);
    }
  }

  // Enumerates all homogenous functions of degree r, including 0.
  BooleanFun homr(n-1);
  while (1) {
    BooleanFun sub0 = this->sub_function(0);
    sub0.add(homr);
    int non0 = sub0.nonlinearity(r-1, upper_bound);
    if (non0 < upper_bound) {
      BooleanFun sub1 = this->sub_function(1);
      sub1.add(homr);
      int non1 = sub1.nonlinearity(r-1, upper_bound-non0);
      if (non0 + non1 < upper_bound) {
        upper_bound = non0 + non1;
      }
    }

    // Find the next homogenous function of degree r.
    // Find the minimal index i such that homr.truth_table[deg_r_x[i]] == 0.
    int i = 0;
    while (i < deg_r_x.size() && homr.anf[deg_r_x.at(i)] == 1) {
      i ++;
    }
    // The last homogenous function of degree r.
    if (i == deg_r_x.size()) {
      break;
    }
    homr.anf[deg_r_x.at(i)] = 1;
    for (int j = 0; j < i; j ++) {
      homr.anf[deg_r_x.at(j)] = 0;
    }
    homr.set_anf_coe_done();
  }

  return upper_bound;
}

// Returns the rth-order nonlinearity.
int BooleanFun::nonlinearity(int r) const {
  return nonlinearity(r, (1<<n));
}

