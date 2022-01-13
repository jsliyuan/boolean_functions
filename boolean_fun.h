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

    // Destructor
    ~BooleanFun();

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
  private:
    // number of variables
    int n;

    // truth table of this Boolean function, of length 2^n
    // value of f(x_1, x_2, ..., x_n) is truth_table[d(x)],
    // where d(x) := x_1*2^{n-1}+x_2*2^{n-2}+...+x_n.
    int* truth_table;

    // algebraic normal form
    // ANF[d(e)] is the coefficient of x1^{e1}x2^{e2}...xn^{en}.
    int* anf;

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
};
