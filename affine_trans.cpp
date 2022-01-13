#include "affine_trans.h"

#include <iostream>

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
  	vec_y[i] = 0;
  	for (int j = 0; j < n; j ++) {
  	  vec_y[i] = (vec_y[i] + vec_x[j]*A[i*n+j] + b[i]) % 2;
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

// Let b[i] = v, where 1 <= i <= n.
// If i is out of range, returns false.
bool AffineTrans::set_b(int i, int v) {
  if (i < 1 || i > n) {
  	return false;
  }

  b[i-1] = v;
  return true;
}

// Gets A[i][j], where 1 <= i, j <= n.
int AffineTrans::get_a(int i, int j) const {
  if (i < 1 || i > n || j < 1 || j > n) {
  	return -1;
  }
  return A[(i-1)*n + j-1];
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
