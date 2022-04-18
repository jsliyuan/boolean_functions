#ifndef BOOLEAN_FUN_H
#define BOOLEAN_FUN_H

#include "affine_trans.h"

#include <cstdarg>
#include <string>

class BooleanFun {
  public:
    // Returns the number of variables.
    int var_num() const;

    // Constructor with parameter (number of variables)
    // Create an all-zero Boolean function in n variables.
    BooleanFun(int n);

    // Reload < opeartor
    bool operator < (const BooleanFun &g) const {
      if (this->n < g.var_num()) {
        return true;
      }
      return this->get_anf() < g.get_anf();
    }

    // Reload = opeartor
    bool operator == (const BooleanFun &g) const {
      if (this->n != g.var_num()) {
        return false;
      }
      return this->get_anf() == g.get_anf();
    }

    // Assignment operator
    BooleanFun& operator=(const BooleanFun& g);

    // Constructor with parameters, where n is the number
    // of variables, and anf is the algebraic normal form.
    // If anf is invalid, we throw an exception.
    // For example,
    // "0": the all-0 Boolean function
    // "1": the all-1 Boolean function
    // "x1x2+1": x1*x2+1
    // "x1x2+x4x5": x1*x2+x4*x5
    // We do not support parenthesis "()" for now.
    // Do not include extra spaces.
    BooleanFun(int n, std::string anf_str);

    // Copy constructor.
    BooleanFun(const BooleanFun& g);

    // Resets the ANF.
    // Both truth table and anf are modified.
    // Returns false if anf_str is invalid.
    bool set_anf(std::string anf_str);

    // Resets the ANF given the coefficient list.
    // Returns false if coe_list is invalid, where
    // coe_list should be a 01 string of length 2^n.
    bool set_coe_list(std::string coe_list);

    // Sets the coefficient d(x) of the ANF to constant c,
    // where d is in [0, 2^n-1], and c is 0 or 1.
    // If d or c is out of range, returns false.
    bool set_anf_coe(int d, int c);

    // Call this function after setting all the coefficients
    // in the ANF.
    // The truth table and degree will be re-computed.
    void set_anf_coe_done();

    // Set the truth_table[x] to v, where
    // x is in [0, 2^n-1], and v is 0 or 1.
    // Returns false if x or v is out of range.
    bool set_truth_table(int x, int v);

    // After setting the truth table, call this function.
    // The degree and ANF will be computed then.
    void set_truth_table_done();

    // Destructor
    ~BooleanFun();

    // Returns the subfunction in n-1 variables by setting
    // x_n to constant c, where c is 0 or 1.
    BooleanFun sub_function(int c) const;

    // Evaluate boolean function at a given point by giving {0,1}^n.
    // We must have num = n; otherwise returns -1.
    int value(int num, ...) const;

    // Evaluate boolean function at a given point, where d
    // is the decimal representation of a vector x in {0,1}^n.
    // d in [0, 2^n-1], otherwise returns -1.
    int value_dec(int d) const;

    // Returns the algebraic normal form as a string. E.g.,
    //   "0"
    //   "1"
    //   "x2+x1+x1x2"
    // The terms are ordered by the lexicographical order (d(x)).
    std::string get_anf() const;

    // Returns anf[2^n] as a 01 string of length 2^n.
    // The order preserves.
    std::string get_coe_list() const;

    // Returns anf[d], where d is in [0, 2^n-1].
    // Returns -1 if d is out of range.
    int get_anf_coe(int d) const;

    // Returns the algebraic degree.
    int get_degree() const;

    // Compares if this Boolean function is equal to f.
    bool is_equal(const BooleanFun& f) const;

    // Takes the negation of this Boolean function, i.e.,
    // let this = f + 1 (over GF(2)).
    // Both truth table and anf are modified.
    void negate();

    // Let this = this + f (over GF(2)).
    // Returns false if #vars(f) != n.
    bool add(const BooleanFun& f);

    // Let this = this * f (over GF(2)).
    // Returns false if #vars(f) != n.
    bool mult(const BooleanFun& f);

    // Apply affine transformation to this Boolean function, i.e.,
    // f = f(T(x)) = f(Ax + b), where T(x) = Ax + b.
    // Returns false if the dimension does not match.
    // Both truth table and anf are updated.
    bool apply_affine_trans(const AffineTrans& trans);

    // Trim all monomials whose degree is less than deg_upper.
    // Both truth table and anf are updated.
    void trim_degree_below(int deg_upper);

    // Returns the Hamming distance between two Boolean functions.
    // If their #variables do not match, return -1.
    int dist(const BooleanFun& f) const;

    // Returns true if this Boolean function is homogeneous
    // as a polynomial over GF(2).
    bool is_homogenous() const;

    // Compute the Walsh transform on w, where w is in [0, 2^n-1]
    // (w1, w2, ..., wn) -> d(w) := w_1*2^{n-1}+w_2*2^{n-2}+...+w_n.
    // W(w) = sum_{x} (-1)^(f(x) + w*x)
    int walsh_transform(int w) const;

    // Returns the first-order nonlinearity, which is
    // 2^{n-1} - max_w |walsh_transform(w)| / 2.
    int nonlinearity() const;

    // Returns the rth-order nonlinearity, where r >= 1.
    int nonlinearity(int r) const;

    // BE CAREFUL!
    // truth table of this Boolean function, of length 2^n
    // value of f(x_1, x_2, ..., x_n) is truth_table[d(x)],
    // where d(x) := x_1*2^{n-1}+x_2*2^{n-2}+...+x_n.
    int* truth_table;

    // BE CAREFUL!
    // algebraic normal form
    // ANF[d(e)] is the coefficient of x1^{e1}x2^{e2}...xn^{en}.
    int* anf;

  private:
    // number of variables
    int n;

    // algebraic degree
    int degree;

    // Compute truth table from anf.
    void anf_to_truth_table();

    // Compute anf from truth table.
    void truth_table_to_anf();

    // Returns the decimal representation of the given term.
    // Example terms: "x1x2x3", "x3x11".
    // Each term is of the form x^a = x1^{a1}x2^{a2}...xn^{an},
    // where a is in {0,1}^n
    // Returns the decimal value of the binary number (a1, a2, ..., an).
    int get_term(std::string term) const;

    // The inverse of the above function.
    // Given the decimal value of the binary number (a1, a2, ..., an),
    // returns the term x^a = prod_{i: a_i=1} xi.
    std::string compose_term(int dec) const;

    // Computes the mobius inversion of source[2^n], and writes
    // the result into dest[2^n].
    // dest[x] = sum_{y <= x bitwise} source[y]
    // The summation is over GF(2).
    void mobius_inversion(int* dest, int* source);

    // Returns the base-2 weight of an integer， i.e., returns the
    // number of one's in its binary representation.
    int weight(int x) const;

    // Computes the algebraic degree, and sets this->degree.
    void compute_degree();

    // Compute the inner product of x and y, viewed as vector {0,1}^n
    int inner_product(int x, int y) const;

    // Returns the rth-order nonlinearity, where r >= 1.
    // Cut down the search if the current value is > upper_bound.
    int nonlinearity(int r, int upper_bound) const;

    // Allocate memory and copy all data from g to this.
    void copy_data(const BooleanFun& g);
};

#endif
