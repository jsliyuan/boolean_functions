#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <string>
#include <unordered_set>

// Permutation class
class Permutation {
  public:
    // Returns the number of variables.
    int var_num() const;

    // Sets to the idenitiy by default;
    Permutation(int n);
    
    //deep copy
    Permutation(const Permutation& P);

    // Destructor.
    ~Permutation();

    //Sets the table of permutation
    //e.g. [2,3,4,5,6,7,8,9,1]
    bool set(int* perm1);

    //Sets the table of permutation
    //e.g. "2,3,4,5,6,7,8,9,1"
    bool set(std::string perm1);
    
    bool set(int idx, int val);
    
    // Return "2,3,4,5,6,7,8,9,1"
    std::string get_str() const;

    const int* get_perm() {
      return perm;
    }

    // Assignment operator
    Permutation& operator=(const Permutation& perm1);
    
    // Reload = opeartor
    bool operator == (const Permutation &p) const {
      if (this->n != p.var_num()) {
        return false;
      }
      return this->get_str() == p.get_str();
    }

    // this = perm * this
    void left_mult(const Permutation& perm1);
    
    // this = this * perm
    void right_mult(const Permutation& perm1);

  private:
    int n;

    // array of length n
    int* perm;

    void copy_data(const Permutation& perm1);
};

#endif


