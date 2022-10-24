/*
PermGroup class can generate all elements in the generalized rotation symmetric class given the generators. 
*/

#ifndef PERM_GROUP_H
#define PERM_GROUP_H

#include <string>
#include <unordered_set>
#include <vector>
#include <set>
#include "permutation.h"
using namespace std;

class PermGroup {
  public:
    
    PermGroup(int n);

    PermGroup(const PermGroup& PG);
    // Destructor.
    ~PermGroup();

    // Assignment operator
    PermGroup& operator=(const PermGroup& PG);
    
    //TODO(jjg): implement== operator when needed
    /*bool operator == (const SymGroup &SG) const {
      if (this->n != this->n) {
        return false;
      }
    //  return this->get_str() == p.get_str();
    }*/

    // Can be called multiple times.
    void add_generator(Permutation perm1) {
      this->generators.push_back(perm1);
    }

    void compute_orbits();

    vector<Permutation> get_elements() {
      return this->elements;
    }

    vector<Permutation> get_generators() {
      return this->generators;
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
    
    void copy_data(const PermGroup& PG);

    vector<Permutation> generators;

     // All elements of the group
    vector<Permutation> elements;

    // Given generators, compute all elements of the group.
    void generate_all();

    vector<vector<int> > orbits;

};

#endif


