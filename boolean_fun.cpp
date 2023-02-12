/*  BooleanFun is class that can be used to set up a Boolean function.
Basic operations such as addition, multiplication, fourier transform, 
changing ANF to truth table (or changing truth table to ANF) 
can occur over Boolean functions in this class.

Moreover, calculating the r-order nonlinearity and Gower U2/U3 norm of 
a Boolean function can be implemented in this class. Please note that it is slow 
to compute higher order nonliearity (r>=3) of Boolean functions.
*/

#include "boolean_fun.h"

#include <memory.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

// BooleanFun constructor with parameter (number of variables)
BooleanFun::BooleanFun(int n) {
  this->n = n;
  this->new_space(n);
  degree = 0;

  // initialize random seed
  srand(time(NULL));
}

// Constructor with parameters, where n is the number
// of variables, and anf_str is the algebraic normal form.
// For example,
//   anf = "x1x2+x3+1"
BooleanFun::BooleanFun(int n, string anf_str) {
  this->n = n;
  this->new_space(n);
  this->set_anf(anf_str);

  // Compute truth_table using anf
  anf_to_truth_table();
  compute_degree();

  // initialize random seed
  srand(time(NULL));
}

// Allocate memory and copy all data from g to this.
void BooleanFun::copy_data(const BooleanFun& g) {
  this->n = g.var_num();
  this->degree = g.get_degree();
  
  memcpy(this->anf, g.anf, (1<<n)*sizeof(int));
  memcpy(this->truth_table, g.truth_table, (1<<n)*sizeof(int));
  memcpy(this->un, g.un, (1<<n)*sizeof(int));
  memcpy(this->fourier_transform, g.fourier_transform, (1<<n)*sizeof(int));
}

// Copy constructor.
BooleanFun::BooleanFun(const BooleanFun& g) {
  new_space(g.var_num());
  copy_data(g);
}

// Assignment operator
BooleanFun& BooleanFun::operator=(const BooleanFun& g) {
  free_space();
  new_space(g.var_num());
  copy_data(g);
  return *this;
}

// Allocate memory for all pointers, including
// truth_table, anf, tmp, fourier_transform
void BooleanFun::new_space(int n) {
  truth_table = new int[1<<n];
  anf = new int[1<<n];
  tmp = new int[1<<n];
  un = new int[1 << n];
  fourier_transform= new int [1<<n];
  memset(truth_table, 0, (1<<n) * sizeof(int));
  memset(anf, 0, (1<<n) * sizeof(int));
  memset(tmp, 0, (1<<n) * sizeof(int));
  memset(un, 0, (1<<n) * sizeof(int));
  memset(fourier_transform, 0, (1<<n) * sizeof(int));
}

void BooleanFun::free_space() {
  if (anf) {
    delete[] anf;
  }
  if (truth_table) {
    delete[] truth_table;
  }
  if (tmp) {
    delete[] tmp;
  }
  if (fourier_transform) {
    delete[] fourier_transform;
  }
  if (un) {
      delete[] un;
  }
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

// Returns anf[2^n] as a 01 string of length 2^n.
// The order preserves.
string BooleanFun::get_coe_list() const {
  string result = "";
  for (int i = 0; i < (1<<n); i ++) {
    if (anf[i] == 0) {
      result += "0";
    }
    if (anf[i] == 1) {
      result += "1";
    }
    if (anf[i] != 0 && anf[i] != 1) {
      cout << "ERROR: invalid anf[" << i << "] = " << anf[i] << endl;
    }
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

// Compute the fast_fourier_transform of truth table tt[1<<n], and writes
// the results into Fourier_arry[1<<n].
void BooleanFun::fast_fourier_transform(int* tt,int* Fourier_arry, int n) const{
  for (int m=0 ; m< (1<<n); m++) {
    if(tt[m] == 1) {
      Fourier_arry[m]=-1;
    } else {
      Fourier_arry[m]=1;
    }
  }
  int i, j, k;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < 1<<(n-1); ++j) {
      k = j << 1;
      tmp[j] = Fourier_arry[k] + Fourier_arry[k + 1];
      tmp[j + (1<<(n-1))] = Fourier_arry[k] - Fourier_arry[k + 1];
    }
    memcpy(Fourier_arry, tmp,  (1<<n)*sizeof(int));
  }
}

// Returns the truth table in its hex format, string of length 2^n / 16.
string BooleanFun::get_truth_table_hex() const {
  string result = "";
  for(int count=0;count<(1<<n);count+=4) {
    int i=count;
    int num;
    num=truth_table[i]*8+truth_table[i+1]*4+truth_table[i+2]*2+truth_table[i+3]*1;
    switch (num) {
      case 0: result.append("0");break;
      case 1: result.append("1");break;
      case 2: result.append("2");break;
      case 3: result.append("3");break;
      case 4: result.append("4");break;
      case 5: result.append("5");break;
      case 6: result.append("6");break;
      case 7: result.append("7");break;
      case 8: result.append("8");break;
      case 9: result.append("9");break;
      case 10: result.append("A");break;
      case 11: result.append("B");break;
      case 12: result.append("C");break;
      case 13: result.append("D");break;
      case 14: result.append("E");break;
      case 15: result.append("F");break;
    }
  }
  return result;
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

// orbit is a list of points, where each is in [0, 2^n-1], v is 0 or 1
// we set the truth table value for all points (in the orbit) to constant v.
bool BooleanFun::set_truth_table_orbit(std::vector<int> orbit, int v) {
  if (v < 0 || v > 1) {
    return false;
  }
  for (int t =0; t<orbit.size(); t++) { 
    if (orbit[t] < 0 || orbit[t] >= (1<<n)) {
      cout<<" ERROR:point "<< t <<" in orbit is out of range"<<endl;
    }
    else {
      truth_table[orbit[t]]=v;
    }
  }
  return true;
}

// After setting the truth table, call this function.
// The degree and ANF will be computed then.
void BooleanFun::set_truth_table_done() {
  this->truth_table_to_anf();
  this->compute_degree();
}

// Convert hexadecimal string to binary string, and 
// set the truth_table[x] to v, where
// x is in [0, 2^n-1], and v is 0 or 1.
// Returns false if x or v is out of range.
bool BooleanFun::set_truth_table_hex(string str) {
  string sReturn;
  unsigned int length=str.length();
  for(int i=0;i<length;i++)
  {
    switch (str[i])
    {
      case '0': sReturn.append("0000");break;
      case '1': sReturn.append("0001");break;
      case '2': sReturn.append("0010");break;
      case '3': sReturn.append("0011");break;
      case '4': sReturn.append("0100");break;
      case '5': sReturn.append("0101");break;
      case '6': sReturn.append("0110");break;
      case '7': sReturn.append("0111");break;
      case '8': sReturn.append("1000");break;
      case '9': sReturn.append("1001");break;
      case 'A': sReturn.append("1010");break;
      case 'a': sReturn.append("1010");break;
      case 'B': sReturn.append("1011");break;
      case 'b': sReturn.append("1011");break;
      case 'C': sReturn.append("1100");break;
      case 'c': sReturn.append("1100");break;
      case 'D': sReturn.append("1101");break;
      case 'd': sReturn.append("1101");break;
      case 'E': sReturn.append("1110");break;
      case 'e': sReturn.append("1110");break;
      case 'F': sReturn.append("1111");break;
      case 'f': sReturn.append("1111");break;
    }
  }
  unsigned int length1=sReturn.length();
  for(int i=0;i<length1;i++)
  {
    switch (sReturn[i])
    {
      case '0': truth_table[i] = 0;break;
      case '1': truth_table[i] = 1;break;
    }
  }
  return true;
}

// Sets the truth table at random, i.e.,
// For every x in [0, 2^n-1], set f(x) = 0 / 1 uniformly
// at random.
void BooleanFun::set_truth_table_random() {
  for (int i = 0; i < (1<<n); i ++) {
    this->truth_table[i] = rand() % 2;
  }
  set_truth_table_done();
}

// Sets the truth table of all orbits at random, i.e.,
// For every orbits[i][j] in [0, 2^n-1], set f(orbits[i][j]) = 0 / 1 uniformly
// at random.
void BooleanFun::set_random_sym( vector<vector<int> > orbit) {
  for(vector<vector<int> >::iterator it=orbit.begin();it!=orbit.end();it++) {
    set_truth_table_orbit((*it), rand()% 2);
  }
  set_truth_table_done();
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

// Resets the ANF given the coefficient list.
// Returns false if coe_list is invalid, where
// coe_list should be a 01 string of length 2^n.
bool BooleanFun::set_coe_list(std::string coe_list) {
  int idx = 0;
  for (int i = 0; i < (1<<n); i ++) {
    while (idx < coe_list.length() &&
           coe_list[idx] != '0' && coe_list[idx] != '1') {
      idx ++;
    }
    if (idx >= coe_list.length()) {
      cout << "ERROR: coe_list is too short!";
      return false;
    }
    anf[i] = (coe_list[idx] == '1' ? 1 : 0);
    idx ++;
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

// Call this function after setting all the coefficients
// in the ANF.
// The truth table and degree will be re-computed.
void BooleanFun::set_anf_coe_done() {
  // Compute truth_table using anf
  anf_to_truth_table();
  compute_degree();
}

// Computes the mobius inversion of source[2^n], and writes
// the result into dest[2^n].
// dest[x] = XOR_{y <= x bitwise} source[y]
void BooleanFun::mobius_inversion(int* dest, int* source) {
  /* Fast approach - time complexity O(n2^n) */
  memcpy(tmp, source, (1<<n)*sizeof(int));

  for (int i = 0; i < n; i ++) {
    int mi = (1<<i);
    for (int k = 0; k < (1<<n); k ++) {
      if ((k & mi) != 0) {
        dest[k] = tmp[k^mi] ^ tmp[k];
      } else {
        dest[k] = tmp[k];
      }
    }
    memcpy(tmp, dest, (1<<n)*sizeof(int));
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

//s is in [0,2^{m}-1]
BooleanFun BooleanFun:: restriction(int m, int s) const {
  BooleanFun sub_f(n-m);
  for(int i=0;i<(1<<(n-m));i++){
    sub_f.truth_table[i]=truth_table[(i<<m) + s];
  }
  sub_f.set_truth_table_done();
  return sub_f;
}

// BooleanFun destructor
BooleanFun::~BooleanFun()
{
  free_space();
}

// Returns the number of variables.
int BooleanFun::var_num() const {
  return n;
}

// Returns the base-2 weight of an integer, i.e., returns the
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

// Cost function used by Kavut and Yucel, who prove that
// CR(1, 9) >= 242.
int BooleanFun::cost() const {
  int buf[(1<<n)];
  int tt[(1<<n)];

  for (int m=0;m< (1<<n);m++) {
    if(truth_table[m] == 1) {
      tt[m]=-1;
    } else {
      tt[m]=1;
    }
  }
  register int i, j, k;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < 1<<(n-1); ++j) {
      k = j << 1;
      buf[j] = tt[k] + tt[k + 1];
      buf[j + (1<<(n-1))] = tt[k] - tt[k + 1];
    }
    memcpy(tt, buf,  (1<<n)*sizeof(int));
  }

  int value=0;
  for (i = 0; i < 1<<(n); ++i) {
    value=value+ (abs(tt[i])*abs(tt[i])-512)*(abs(tt[i])*abs(tt[i])-512);
  }

  return value;
}

// Returns the first-order nonlinearity, which is
// 2^{n-1} - max_w |walsh_transform(w)| / 2.
// Computed using FFT (Fast Fourier Transform)
// Time complexity is O(n2^n)
int BooleanFun::nonlinearity() const {
 this->fast_fourier_transform(truth_table,fourier_transform,n);
  int max = 0;
  for (int i = 0; i < 1<<(n); ++i) {
    if (abs(fourier_transform[i]) > max) {
      max = abs(fourier_transform[i]);
    }
  }
 return (1<<(n-1)) - (max >> 1);
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

// Returns the truth table, which is an array of length 2^n.
// Read-only.
const int* BooleanFun::get_truth_table_ptr() {
  return truth_table;
}

// Returns the anf, which is an array of length 2^n.
// Read-only.
const int* BooleanFun::get_anf_ptr() {
  return anf;
}

// Converts the truth table to uni-variate representation
void BooleanFun::truth_table_to_univariate(Field& f) {
    int m = f.m;
    int* mg = f.mg;
    un[m] = 0;
    for (int i = 0; i < m; i++) {
        int t = 0;
        for (int j = 0; j < m; j++) {
            if (truth_table[mg[j]] == 1) {
                int p = (-i * j) % m;
                if (p < 0) {
                    p += m;
                }
                t = f.addTab[t][mg[p]];
            }
        }
        un[i] = t;
    }
    int sum = 0;
    for (int i = 0; i < m + 1; i++) {
        sum += truth_table[i];
    }
    if (sum % 2 != 0) {
        un[0] += 1;
        un[0] %= 2;
        un[m] = 1;
    }
}

void BooleanFun::truth_table_to_univariate(Field_X& f) {
    int m = f.m;
    int* mg = f.mg;
    un[m] = 0;
    for (int i = 0; i < m; i++) {
        int t = 0;
        for (int j = 0; j < m; j++) {
            if (truth_table[mg[j]] == 1) {
                int p = (-i * j) % m;
                if (p < 0) {
                    p += m;
                }
                t = f.add(t, mg[p]); 
            }
        }
        un[i] = t;
    }
    int sum = 0;
    for (int i = 0; i < m + 1; i++) {
        sum += truth_table[i];
    }
    if (sum % 2 != 0) {
        un[0] += 1;
        un[0] %= 2;
        un[m] = 1;
    }
}

// Decides if the vector boolean function with un as its univariate coefficients is boolean
bool BooleanFun::is_univariate_boolean(Field& f) {
    int m = f.m;
    if (un[0] != 0 && un[0] != 1) { return false; }
    if (un[m] != 0 && un[m] != 1) { return false; }
    for (int i = 1; i < m; i++) {
        int j = (2 * i) % m;
        if (un[j] != f.mulTab[un[i]][un[i]]) {
            return false;
        }
    }
    return true;
}

bool BooleanFun::is_univariate_boolean(Field_X& f) {
    int m = f.m;
    if (un[0] != 0 && un[0] != 1) { return false; }
    if (un[m] != 0 && un[m] != 1) { return false; }
    for (int i = 1; i < m; i++) {
        int j = (2 * i) % m;
        if (un[j] != f.mul(un[i],un[i])) {
            return false;
        }
    }
    return true;
}

// Calculates the value in x of the boolean function with un as its uni-variate representation.
void BooleanFun::univariate_to_truth_table(Field& f) {
    int m = f.m;
    truth_table[0] = un[0];
    for (int x = 1; x < m + 1; x++) {  //current variable
        int t = 1;
        for (int j = 0; j <= m; j++) {
            truth_table[x] = f.addTab[truth_table[x]][f.mulTab[t][un[j]]];
            t = f.mulTab[x][t]; //x^j
        }
    }
}

void BooleanFun::univariate_to_truth_table(Field_X& f) {
    int m = f.m;
    truth_table[0] = un[0];
    for (int x = 1; x < m + 1; x++) {  //current variable
        int t = 1;
        for (int j = 0; j <= m; j++) {
            truth_table[x] = f.add(truth_table[x], f.mul(t, un[j]));
            t = f.mul(x,t); //x^j
        }
    }
}

// str is an univariate representation of vector boolean function.
// For example:
// str="x^3+x^7" corresponds to the boolean function tr(x^3+x^7).
void BooleanFun::set_trace_univariate(const string& str,Field& f) {
    for (int i = 0; i < 1 << n; i++) {
        un[i] = 0;
    }
    //the univariate representation of the str
    int state = 0;  //记录当前状态. 0:一个项开始; 1:遇到x,准备遍历指数; 
    int cur_coe = 0;  //记录系数
    int cur_index = 0;  //记录项的指数
    for (char c : str) {
        if (isdigit(c)) {
            if (state == 0) {
                cur_coe = cur_coe * 10 + (c - '0');
            }
            else if (state == 1) {
                cur_index = cur_index * 10 + (c - '0');
            }
        }
        else if (c == 'x') {
            state = 1;
            if (cur_coe == 0) {
                cur_coe = 1;
            }
        }
        else if (c == '+') {
            state = 0;
            un[cur_index] = cur_coe;
            cur_coe = 0; cur_index = 0;
        }
    }
    un[cur_index] = cur_coe;

    //trace
   /* memcpy(tmp, un, (1 << n) * sizeof(int));
    for (int i = 0; i < 1 << n; i++) {
        un[i] = 0;
    }*/
    
    //un is incorrect...
    univariate_to_truth_table(f);
    for (int i = 0; i < 1 << n;i++) {
        truth_table[i] = f.tr(truth_table[i]);
    }
    //f->Tr(un, truth_table);
    //truth_table_to_anf();
}

void BooleanFun::set_trace_univariate(const string& str, Field_X& f) {
    for (int i = 0; i < 1 << n; i++) {
        un[i] = 0;
    }
    //the univariate representation of the str
    int state = 0;  //记录当前状态. 0:一个项开始; 1:遇到x,准备遍历指数; 
    int cur_coe = 0;  //记录系数
    int cur_index = 0;  //记录项的指数
    for (char c : str) {
        if (isdigit(c)) {
            if (state == 0) {
                cur_coe = cur_coe * 10 + (c - '0');
            }
            else if (state == 1) {
                cur_index = cur_index * 10 + (c - '0');
            }
        }
        else if (c == 'x') {
            state = 1;
            if (cur_coe == 0) {
                cur_coe = 1;
            }
        }
        else if (c == '+') {
            state = 0;
            un[cur_index] = cur_coe;
            cur_coe = 0; cur_index = 0;
        }
    }
    un[cur_index] = cur_coe;

    //trace
   /* memcpy(tmp, un, (1 << n) * sizeof(int));
    for (int i = 0; i < 1 << n; i++) {
        un[i] = 0;
    }*/

    //un is incorrect...
    univariate_to_truth_table(f);
    for (int i = 0; i < 1 << n; i++) {
        truth_table[i] = f.tr(truth_table[i]);
    }
    //f->Tr(un, truth_table);
    //truth_table_to_anf();
}

// Returns the un.
// Read-only.
const int* BooleanFun::get_un_ptr() {
    return un;
}


