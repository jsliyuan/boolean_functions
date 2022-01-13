#include "upper_diag_generator.h"

#include <iostream>

// Constructor with parameter (dimension).
// Creates an identity affine transformation.
UpperDiagGenerator::UpperDiagGenerator(int n) {
  this->n = n;
  this->init();
}

// Returns the current affine transformaton.
AffineTrans* UpperDiagGenerator::get_affine_trans() const {
  return this->current;
}

// Initialize. That is, set current to the identity matrix.
// You don't need to call it for the first time.
void UpperDiagGenerator::init() {
  current = new AffineTrans(n);
  for (int i = 1; i <= n; i ++) {
  	current->set_a(i, i, 1);
  }
}

// Generates the next upper-diagonal affine transformation.
bool UpperDiagGenerator::next() {
  // Find the first 0 in the strict upper-diagonal part.
  int idx_i = 0, idx_j = 0;
  for (int i = 1; i <= n; i ++) {
    for (int j = i+1; j <= n; j ++) {
      if (this->current->get_a(i, j) == 0) {
        idx_i = i;
        idx_j = j;
        break;
      }
    }
    if (idx_i > 0) {
      break;
    }
  }
  // Hits the last one.
  if (idx_i == 0) {
    return false;
  }

  this->current->set_a(idx_i, idx_j, 1);
  // Erase all the previous 1's.
  for (int i = 1; i <= idx_i; i ++) {
    for (int j = i+1; j <= n; j ++) {
      if (i == idx_i && j == idx_j) {
        break;
      }
      this->current->set_a(i, j, 0);
    }
  }
  return true;
}