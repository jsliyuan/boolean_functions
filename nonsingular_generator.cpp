#include "nonsingular_generator.h"

using namespace std;

// Constructor with parameter (dimension).
// Creates an identity affine transformation.
NonsingularGenerator::NonsingularGenerator(int n) {
  this->n = n;
  this->init();
}

// Returns the current affine transformaton.
AffineTrans* NonsingularGenerator::get_affine_trans() const {
  return this->current;
}

// Initialize. That is, set current to the identity matrix.
// You don't need to call it for the first time.
void NonsingularGenerator::init() {
  current = new AffineTrans(n);
  for (int i = 1; i <= n; i ++) {
  	current->set_a(i, n-i+1, 1);
  }
  this->row_span_2n =  this->current->get_rows_span(2, n);
}

// Generates the next nonsingular affine transformation.
bool NonsingularGenerator::next() {
  // Find the first i, such that {ai+delta, a_{i+1}, ..., a_{n-1}} are
  // linearly independent.
  int i = 1;
  while (i <= n) {
    int ai = this->current->get_a_row(i) + 1;
    unordered_set<int> span;
    if (i > 1) {
      span = this->current->get_rows_span(i + 1, n);
    };
    while (ai < (1 << n)) {
      if (i > 1 && span.find(ai) == span.end()) {
        break;
      }
      if (i == 1 && this->row_span_2n.find(ai) == row_span_2n.end()) {
        break;
      }
      ai = ai + 1;
    }
    if (ai < (1 << n)) {
      this->current->set_row_a(i, ai);
      break;
    }
    i = i + 1;
  }
  // Reach the last nonsingular affine transformation.
  if (i > n) {
    return false;
  }

  for (int k = i-1; k >= 1; k --) {
    int ak = 0;
    unordered_set<int> span = this->current->get_rows_span(k + 1, n);
    while (span.find(ak) != span.end()) {
      ak = ak + 1;
    }
    this->current->set_row_a(k, ak);
  }

  if (i > 1) {
    row_span_2n = this->current->get_rows_span(2, n);
  }
  return true;
}