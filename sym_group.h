#ifndef SYM_GROUP_H
#define SYM_GROUP_H

#include <string>
#include <unordered_set>
#include <vector>
#include "permutation.h"
using namespace std;

class SymGroup {
  public:
    
    SymGroup(int n);

    SymGroup(const SymGroup& SG);
    // Destructor.
    ~SymGroup();

    // Assignment operator
    SymGroup& operator=(const SymGroup& SG);
    
    bool operator == (const SymGroup &SG) const {
      if (this->n != this->n) {
        return false;
      }
    //  return this->get_str() == p.get_str();
    }

   
    void set_generator(Permutation perm) {
      generators.push_back(perm);
    }
    // Can be called multiple times.
    void add_generator(Permutation perm) {
      generators.push_back(perm);
    }

    void compute_orbits();

   vector<Permutation> get_elements() {
     return this->elements;
   }

    int get_orbits_number() const;

    // x is between [1,2^n]
    // return the orbit of x
    std::vector<int> get_orbit(int x);

    // return the i-1 th orbit  
    std::vector<int> get_full_orbit(int i) const;

    int get_n() const;

    int group_size() const {
      return this->elements.size();
    }

    std::vector< std::vector<int> > get_all_orbits();
    
  private:
    // dimension
    int n;
    
    void copy_data(const SymGroup& SG);

    vector<Permutation> generators;

     // All elements of the group
    vector<Permutation> elements;

    // Given generators, compute all elements of the group.
    void generate_all();

    std::vector<vector<int> > orbits;

};

#endif


