#ifndef ROTATIONSYM_H
#define ROTATIONSYM_H

#include <string>
#include <unordered_set>
#include <vector>
#include "permutation.h"
using namespace std;
// Affine transformation Ax + b: GF(2)^n -> GF(2)^n,
// where A is an n*n matrix, and b is an n*1 array.
class RotationSym {
  public:
    // Constructor with parameter (dimension).
    // Create an all-zero affine transformation.
    RotationSym(int n);

    // Copy constructor.
    // Performs a deep copy.
    RotationSym(const RotationSym& RS);
    // Destructor.
    ~RotationSym();

    // Assignment operator
    RotationSym& operator=(const RotationSym& RS);
    
    bool operator == (const RotationSym &RS) const {
      if (this->n != this->n) {
        return false;
      }
    //  return this->get_str() == p.get_str();
    }

    int get_orbits_number() const;

    // x is between [1,2^n]
    // return the orbit of x
    std::vector<int> get_orbit(int x);

    // return the ith orbit  
    std::vector<int> get_full_orbit(int i) const;

    int get_n() const;
    
  private:
    // dimension
    int n;
    
    void copy_data(const RotationSym& G);

    std::vector<Permutation> perms;

    std::vector<vector<int> > orbits;
};

#endif


