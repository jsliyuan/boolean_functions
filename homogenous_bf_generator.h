#ifndef HOMOGENOUS_BF_GENERATOR_H
#define HOMOGENOUS_BF_GENERATOR_H

#include "boolean_fun.h"

#include <vector>

// Generates all homogenous Boolean functions in n-variables
// with degree r, where r and n are given in the constructor.
// For convenience, the first is the zero Boolean function.
class HomogenousBfGenerator {
  public:
    // Constructor with parameter (dimension), where
    // n >= 1 and 0 <= r <= n.
    HomogenousBfGenerator(int n, int r);

    // Initialize. Set the first Boolean function to zero.
    // You don't need to call it for the first time.
    void init();

    // Returns the current Boolean function.
    BooleanFun* get_boolean_fun() const;

    // Generates the next homogenous Boolean function of
    // degree r.
    // Returns false if it hits the last one.
    bool next();
  private:
    // dimension
    int n;

    // degree
    int r;

    // current Boolean function
    BooleanFun* current;

    // ANF coefficients with weight r
    // The size is {n choose r}.
    std::vector<int> coefficients;

    // Returns the number of one's in the
    // binary representation of x.
    int weight(int x);
};

#endif

