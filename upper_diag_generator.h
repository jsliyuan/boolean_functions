#ifndef UPPER_DIAG_GENERATOR_H
#define UPPER_DIAG_GENERATOR_H

#include "affine_trans.h"

// Generates all affine transformations Ax+b, where
// A is a upper diagonal matrix, and b = 0.
class UpperDiagGenerator {
  public:
    // Constructor with parameter (dimension).
    // Creates an identity affine transformation.
    UpperDiagGenerator(int n);

    // Returns the current affine transformaton.
    // The initial one is the diagonal matrix.
    AffineTrans* get_affine_trans() const;

    // Initialize. That is, set current to the identity matrix.
    // You don't need to call it for the first time.
    void init();

    // Generates the next affine transformation, which
    // is upper diagonal. For example,
    // 1 0 0 => 1 1 0 => 1 0 1 => 1 1 1 => ... => 1 1 1
    // 0 1 0    0 1 0    0 1 0    0 1 0           0 1 1
    // 0 0 1    0 0 1    0 0 1    0 0 1           0 0 1
    // Returns false it hits the last one.
    bool next();
  private:
  	// dimension
    int n;

    // current affine transformation.
    AffineTrans* current;
};

#endif
