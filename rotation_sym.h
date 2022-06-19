#ifndef ROTATION_SYM_H
#define ROTATION_SYM_H

#include <string>
#include <unordered_set>
#include <vector>
#include "permutation.h"

using namespace std;

class RotationSym {
  public:
    // Initialize Rotationsym
    // generate all permutations of rotation symmetric class and orbits
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
    // return the orbit of the position x
    std::vector<int> get_orbit(int x);

    // return the i-1 th orbit  
    std::vector<int> get_full_orbit(int i) const;

    int get_n() const;

    std::vector< std::vector<int> > get_all_orbits();
    
  private:
    // number of variables
    int n;
    
    void copy_data(const RotationSym& G);
    
    //store permutations
    std::vector<Permutation> perms;

    //store all orbits 
    std::vector<vector<int> > orbits;
};

#endif
