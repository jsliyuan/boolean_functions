#ifndef NONSINGULAR_GENERATOR_H
#define NONSINGULAR_GENERATOR_H

#include "affine_trans.h"

// Generates all affine transformations Ax+b, where
// A is a nonsingular matrix, and b = 0.
class NonsingularGenerator {
  public:
    // Constructor with parameter (dimension).
    // Creates an identity affine transformation.
    NonsingularGenerator(int n);

    // Returns the current affine transformaton.
    // The initial one is the diagonal maxtir I_n.
    AffineTrans* get_affine_trans() const;

    // Initialize. That is, set current to the identity matrix.
    // You don't need to call it for the first time.
    void init();

    // Generates the next nonsingular transformation.
    // For example,
    // 0 0 1 => 1 0 1 => 0 1 1 => 1 1 1 => ... => 1 0 1
    // 0 1 0    0 1 0    0 1 0    0 1 0           0 1 1
    // 1 0 0    1 0 0    1 0 0    1 0 0           1 1 1
    // Returns false it hits the last one.
    bool next();
  private:
  	// dimension
    int n;

    // current affine transformation.
    AffineTrans* current;

    // Span of the (row2, row3, ..., rown) in current.
    // This is for speeding the search process.
    std::unordered_set<int> row_span_2n;
};

#endif
