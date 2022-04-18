#include "affine_trans.h"

#include <cstring>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

// Constructor with parameter (dimension).
AffineTrans::AffineTrans(int n) {
  this->n = n;
  A = new int[n*n];
  b = new int[n];
  for (int i = 0; i < n*n; i ++) {
    A[i] = 0;
  }
  for (int i = 0; i < n; i ++) {
    b[i] = 0;
  }

  // initialize random seed
  srand(time(NULL));
}

// Constructor with parameters n, A and b.
AffineTrans::AffineTrans(int n, int* A, int* b) {
  this->n = n;
  this->A = new int[n*n];
  for (int i = 0; i < n*n; i ++) {
  	this->A[i] = A[i];
  }
  this->b = new int[n];
  for (int i = 0; i < n; i ++) {
  	this->b[i] = b[i];
  }
}

// Allocate memory and copies all data from T to this.
void AffineTrans::copy_data(const AffineTrans& T) {
  this->n = T.get_n();
  this->A = new int[n*n];
  this->b = new int[n];
  memcpy(this->A, T.A, n*n*sizeof(int));
  memcpy(this->b, T.b, n*sizeof(int));
}

// Copy constructor.
// Performs a deep copy.
AffineTrans::AffineTrans(const AffineTrans& T) {
  copy_data(T);
}

// Assignment constructor
AffineTrans& AffineTrans::operator=(const AffineTrans& T) {
  if (A) {
    delete A;
  }
  if (b) {
    delete b;
  }
  copy_data(T);

  return *this;
}

// Constructor with n and (A, b) in string format, e.g.,
// [100000 010000 001000 000100 000010 000001]100000
AffineTrans::AffineTrans(int n, std::string str) {
  this->n = n;
  A = new int[n*n];
  b = new int[n];

  this->set_ab(str);
}

// Destructor
AffineTrans::~AffineTrans() {
  if (A) {
    delete A;
  }
  if (b) {
    delete b;
  }
}

// Given a string, set A, b. E.g.,
// [100000 010000 001000 000100 000010 000001]100000
bool AffineTrans::set_ab(string str) {
  int idx = 0;
  for (int i = 0; i < n*(n+1); i ++) {
    while (idx < str.length() && str[idx] != '0' && str[idx] != '1') {
      idx ++;
    }
    if (idx >= str.length()) {
      return false;
    }
    int val = (str[idx] == '1' ? 1 : 0);
    if (i < n*n) {
      A[i] = val;
    } else {
      b[i-n*n] = val;
    }

    idx ++;
  }

  return true;
}

// Returns A and b in string format, e.g.,
// [100000 010000 001000 000100 000010 000001]100000
std::string AffineTrans::get_ab_str() const {
  string result = "[";
  // Append A
  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < n; j ++) {
      result += std::to_string(A[i*n+j]);
    }
    if (i < n-1) {
      result += " ";
    } else {
      result += "]";
    }
  }

  // Append b
  for (int i = 0; i < n; i ++) {
    result += std::to_string(b[i]);
  }

  return result;
}

// Returns Ax + b, where both x and the result
// is in the decimal representation.
// Point (x1, x2, ..., xn) is represented by
// x := x_1*2^{n-1}+x_2*2^{n-2}+...+x_n.
// Returns -1 if x out of range [0, 2^n-1]
int AffineTrans::apply(int x) const {
  if (x < 0 || x >= (1<<n)) {
  	return -1;
  }

  // Convert x to a vector.
  int vec_x[n];
  for (int i = n-1; i >= 0; i --) {
  	vec_x[i] = x % 2;
  	x = x / 2;
  }

  // y = Ax + b
  // y_i = sum_j A_{i,j} x_j + b_i
  int vec_y[n];
  int dec = 0;
  for (int i = 0; i < n; i ++) {
  	vec_y[i] = b[i];
  	for (int j = 0; j < n; j ++) {
  	  vec_y[i] = (vec_y[i] + vec_x[j]*A[i*n+j]) % 2;
  	}
  	dec = dec*2 + vec_y[i];
  }

  return dec;
}

// Returns a as n*n matrix in string, for example,
// 1 0 1\n
// 0 1 0\n
// 0 0 1
std::string AffineTrans::get_a_str() const {
  string result;
  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < n; j ++) {
      result = result + std::to_string(A[i*n+j]);
      if (j < n-1) {
      	result = result + " ";
      }
    }
    if (i < n-1) {
      result = result + "\n";
    }
  }

  return result;
}

// Returns b as vector, for example,
// 1 0 1
std::string AffineTrans::get_b_str() const {
  string result;
  for (int i = 0; i < n; i ++) {
    result = result + std::to_string(b[i]);
    if (i < n-1) {
    	result = result + " ";
    }
  }

  return result;
}

// Let A[i][j] = v, where 1 <= i, j <= n.
// If i or j is out of range, returns false.
bool AffineTrans::set_a(int i, int j, int v) {
  if (i < 1 || i > n || j < 1 || j > n) {
    return false;
  }

  A[(i-1)*n + j-1] = v;
  return true;
}

// Set the entire row i, where v is the decimial representation
// of (A[i][n], A[i][n-1], ..., A[i][1])_2.
// If i or v is out of range, returns false.
bool AffineTrans::set_row_a(int i, int v) {
  if (i < 1 || i > n || v < 0 || v >= (1<<n)) {
    return false;
  }

  // Caculate the index of [i][1].
  int idx = (i-1)*n + 0;
  for (int k = 1; k <=n; k ++) {
    A[idx] = v % 2;
    v = v / 2;
    idx = idx + 1;
  }

  return true;
}

// Let b[i] = v, where 1 <= i <= n.
// If i is out of range, returns false.
bool AffineTrans::set_b(int i, int v) {
  if (i < 1 || i > n) {
  	return false;
  }

  b[i-1] = v;
  return true;
}

// Set the matrix randomly, and make sure it is nonsingular, i.e.,
// determinant is 1.
void AffineTrans::set_random() {
  while (1) {
    for (int i = 0; i < n*n; i ++) {
      A[i] = rand() % 2;
    }
    if (det() == 1) {
      break;
    }
  }
}

// Set the vector randomly.
void AffineTrans::set_random_b() {
  for (int i = 0; i < n; i ++) {
    b[i] = rand() % 2;
  }
}

// Gets A[i][j], where 1 <= i, j <= n.
int AffineTrans::get_a(int i, int j) const {
  if (i < 1 || i > n || j < 1 || j > n) {
  	return -1;
  }
  return A[(i-1)*n + j-1];
}

// Gets A[i][1], A[i][2], ..., A[i][n] as an integer
// A[i][1] + A[i][2]*2 + ... + A[i][n]*2^{n-1}
// in range [0, 2^n-1].
// Returns -1 if i is not in [1, n].
int AffineTrans::get_a_row(int i) const {
  if (i < 1 || i > n) {
    return -1;
  }
  // Get the index of A[i][n]
  int idx = (i-1)*n + n-1;
  int sum = 0;
  for (int k = 1; k <= n; k ++) {
    sum = sum*2 + A[idx];
    idx = idx-1;
  }

  return sum;
}

std::unordered_set<int> AffineTrans::get_rows_span(int i, int j) const {
  if (i < 1) {
    i = 1;
  }
  if (j > n) {
    j = n;
  }
  std::unordered_set<int> result;
  result.insert(0);
  for (int k = i; k <= j; k ++) {
    std::unordered_set<int> temp = result;
    int ai = this->get_a_row(k);
    for (int element : temp) {
      // insert element + ai (over GF(2))
      result.insert((element ^ ai));
    }
  }

  return result;
}

// Gets b[i], where 1 <= i <= n.
// Returns -1 if i is out of range.
int AffineTrans::get_b(int i) const {
  if (i < 1 || i > n) {
  	return -1;
  }
  return b[i];
}

// Returns the dimension n.
int AffineTrans::get_n() const {
  return n;
}

int AffineTrans::det() const {
  int M[n][n];
  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < n; j ++) {
      M[i][j] = A[i*n+j];
    }
  }

  for (int i = 0; i < n; i ++) {
    // Find a row such that the jth column is nonzero
    int k = i;
    while (k < n && M[k][i] == 0) {
      k ++;
    }

    // If cannot find, the det is zero
    if (k == n) {
      return 0;
    }

    // swap row i and row k
    if (k > i) {
      int tmp;
      for (int j = 0; j < n; j ++) {
        tmp = M[i][j];
        M[i][j] = M[k][j];
        M[k][j] = tmp;
      }
    }

    // Gaussian elimination
    for (int r = k+1; r < n; r ++) {
      if (M[r][i] == 1) {
        for (int j = 0; j < n; j ++) {
          M[r][j] = M[r][j] ^ M[i][j];
        }
      }
    }
  }

  return 1;
}

// Let A := A^{-1}.
// If A is not invertible, returns false.
bool AffineTrans::inverse() {
  if (det() == 0) {
    return false;
  }

  int inv[n][n];
  AffineTrans minor(n-1);
  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < n; j ++) {
      // Take the (n-1)*(n-1) minor by deleting ith row and jth column
      int y = 0;
      for (int x = 0; x < n*n; x ++) {
        int xi = x / n;
        int xj = x % n;
        if (xi == j || xj == i) {
          continue;
        }
        minor.set_a(y / (n-1)+1, y % (n-1)+1, A[x]);
        y ++;
      }
      inv[i][j] = minor.det();
    }
  }

  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < n; j ++) {
      A[i*n + j] = inv[i][j];
    }
  }

  return true;
}

// Helper function, matrix multplication
// n is the dimension, and dest = M1*M2
// M[i][j] -> M[(i-1)*n + (j-1)]
void AffineTrans::matrix_mult(int n, int* dest, int* M1, int* M2) {
  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < n; j ++) {
      // dest[i+1][j+1]
      dest[i*n+j] = 0;
      for (int k = 0; k < n; k ++) {
        // dest[i+1][j+1] += M1[i+1][k+1]*M2[k+1][j+1]
        dest[i*n+j] = dest[i*n+j] ^ (M1[i*n+k] & M2[k*n+j]);
      }
    }
  }
}

// Helper function, matrix * vector of dimension n
// dest = A*b
// A[i][j] -> A[(i-1)*n + (j-1)]
void AffineTrans::matrix_vec_mult(int n, int *dest, int* A, int* b) {
  // dest = A*b
  // => dest[i] = \sum_j A[i][j]*b[j]
  for (int i = 0; i < n; i ++) {
    dest[i] = 0;
    for (int j = 0; j < n; j ++) {
      dest[i] = dest[i] ^ (A[i*n+j] & b[j]);
    }
  }
}

// Let this = this * T, where T is applied first, i.e.,
// this(T(x)) = this(T.Ax + T.b)
//            = A*T.Ax + A*T.b + b
// Returns false if the dimension does not match.
bool AffineTrans::mult(const AffineTrans& T) {
  if (this->n != T.get_n()) {
    return false;
  }

  int new_A[n*n];
  int new_b[n];

  matrix_mult(n, new_A, this->A, T.A);
  matrix_vec_mult(n, new_b, this->A, T.b);

  memcpy(A, new_A, n*n*sizeof(int));
  for (int i = 0; i < n; i ++) {
    b[i] = b[i] ^ new_b[i];
  }
  return true;
}
