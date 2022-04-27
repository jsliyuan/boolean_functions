#include "boolean_fun.h"
#include "affine_trans.h"

#include <iostream>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

// Read Boolean function ANF from file, and save the string to fn_set.
// File format:
// ANF (string)
// r (int)
// ANF (string)
// r (int)
// ...
// 2^22 ANFs in total
void read_bfs_from_file(string file_name, int r, set<string> *fn_set) {
  ifstream myfile;
  myfile.open(file_name);
  string anf;
  int val;
  for (int i = 0; i < (1<<22); i ++) {
    myfile >> anf;
    myfile >> val;
    if (val == r) {
      fn_set->insert(anf);
    }
  }

  cout << "Read " << fn_set->size() << " boolean functions from file " << file_name << endl;
  myfile.close();
}

// Read total affine transformations from file, format:
// [000111 100011 010001 110100 011001 001010]000000
// Set b = 0, and let A = A^{-1}.
void read_affine_trans_from_file(string file_name, int total, vector<AffineTrans> *trans) {
  ifstream myfile;
  myfile.open(file_name);
  string aft_str;
  for (int i = 0; i < total; i ++) {
    getline(myfile, aft_str);
    AffineTrans *aft = new AffineTrans(6, aft_str);
    aft->set_b(1, 0);
    aft->set_b(2, 0);
    aft->set_b(3, 0);
    aft->set_b(4, 0);
    aft->set_b(5, 0);
    aft->set_b(6, 0);
    aft->inverse();
    trans->push_back(*aft);
  }

  cout << "Read " << trans->size() << " affine transformations from file " << file_name << endl;
  myfile.close();
}

int main() {
  set<string> Ff6_6;
  read_bfs_from_file("Ff6.txt", 6, &Ff6_6);

  set<string> Ff10_15;
  read_bfs_from_file("Ff10.txt", 15, &Ff10_15);

  vector<AffineTrans> trans;
  read_affine_trans_from_file("fn10_af.txt", 65112, &trans);

  int total_t = 0;
  for (const AffineTrans& aft : trans) {
    // Compute A^{-1}*F_fn6(6)
    vector<BooleanFun> S;
    for (const string& anf : Ff6_6) {
      BooleanFun fn(6, anf);
      fn.apply_affine_trans(aft);
      fn.trim_degree_below(4);
      S.push_back(fn);
    }

    // Enumerate g
    for (const string& t_anf : Ff10_15) {
      BooleanFun g(6, t_anf);
      g.add(S.at(0));
      bool all_in = true;
      for (int i = 1; i < S.size(); i ++) {
        BooleanFun sum = g;
        g.add(S.at(i));
        if (Ff10_15.find(g.get_anf()) == Ff10_15.end()) {
          all_in = false;
          break;
        }
      }
      if (all_in) {
        cout << "Bad news!" << endl;
        cout << aft.get_ab_str() << endl;
      }
    }
    
    total_t ++;
    if (total_t % 10 == 0) {
      cout << total_t << endl;
    }
  }

  return 0;
}