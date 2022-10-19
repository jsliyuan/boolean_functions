/*  BooleanFun is class that can be used to set up a Boolean function.
Basic operations such as addition, multiplication, fourier transform, 
changing ANF to truth table (or changing truth table to ANF) 
can occur over Boolean functions in this class.

Moreover, calculating the r-order nonlinearity and Gower U2/U3 norm of 
a Boolean function can be implemented in this class. Please note that it is slow 
to compute higher order nonliearity (r>=3) of Boolean functions.
*/

#ifndef BOOLEAN_FUN_H
#define BOOLEAN_FUN_H

#include "affine_trans.h"
#include "Galois_field.cpp"

#include <cstdarg>
#include <string>
#include <vector>

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
      return this->get_truth_table_hex() < g.get_truth_table_hex();
    }

    // Reload = opeartor
    bool operator == (const BooleanFun &g) const {
      if (this->n != g.var_num()) {
        return false;
      }
      return this->get_truth_table_hex() == g.get_truth_table_hex();
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

    // orbit is a list of points, where each is in [0, 2^n-1], v is 0 or 1
    // we set the truth table value for all points (in the orbit) to constant v.
    bool set_truth_table_orbit(std::vector<int> orbit, int v);
  
    // After setting the truth table, call this function.
    // The degree and ANF will be computed then.
    void set_truth_table_done();

    //Convert hexadecimal string to binary string, and 
    // set the truth_table[x] to v, where
    // x is in [0, 2^n-1], and v is 0 or 1.
    // Returns false if x or v is out of range.
    bool set_truth_table_hex(std::string str);
  
    // Sets the truth table at random, i.e.,
    // For every x in [0, 2^n-1], set f(x) = 0 / 1 uniformly
    // at random.
    void set_truth_table_random();

    // Sets the truth table of all orbits at random, i.e.,
    // For every orbits[i][j] in [0, 2^n-1], set f(orbits[i][j]) = 0 / 1 uniformly
    // at random.
    void set_random_sym( std::vector<std::vector<int> > orbit);
  
    // Destructor
    ~BooleanFun();

    // Returns the subfunction in n-1 variables by setting
    // x_n to constant c, where c is 0 or 1.
    BooleanFun sub_function(int c) const;
  
    // compute f_s(x)=f(x,s);
    BooleanFun restriction(int m, int s) const ;

    // Returns the dirivative in direction h, denoted by D_h(f),
    // defined as f(x) + f(x+h).
    // h is in [0, 2^n-1].
    BooleanFun derivative(int h) const;

    // Returns the fourth power of Gowers norm U2, which is exactly
    // sum_x ^f(x)^4.
    double Gowers_norm_u2() const;

    // Returns the 8th power of Gowers norm U3, which is
    // exp_h Gowers_norm_u2(D_h(f)).
    double Gowers_norm_u3() const;

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

    // Returns the truth table in its hex format, string of length 2^n / 16.
    std::string get_truth_table_hex() const;
  
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

    // Cost function used by Kavut and Yucel, who prove that
    // CR(1, 9) >= 242.
    int cost() const;  
  
    // Returns the first-order nonlinearity, which is
    // 2^{n-1} - max_w |walsh_transform(w)| / 2.
    // Computed using FFT (Fast Fourier Transform)
    // Time complexity is O(n2^n)
    int nonlinearity() const;

    // Returns the rth-order nonlinearity, where r >= 1.
    int nonlinearity(int r) const;

    // Returns the truth table, which is an array of length 2^n.
    // Read-only.
    const int* get_truth_table_ptr();

    // Returns the anf, which is an array of length 2^n.
    // Read-only.
    const int* get_anf_ptr();

    // Converts the truth table to univariate representation.
    void truth_table_to_univariate(Field* f);

    // Decides if the vector boolean function with un as its univariate coefficients is boolean.
    bool is_univariate_boolean(Field* f);

    // Calculates the value in x of the boolean function with un as its univariate representation.
    void univariate_to_truth_table(Field* f);

    // str is an univariate representation.
    // For example:
    // "x^3+x^7" => un[3]=un[7]=1,un[i]=0,i!=3,7.
    void set_univariate(const string& str);

    // Returns the un.
    // Read-only.
    const int* get_un_ptr();

  protected:
    // Returns the dirivative in direction h, denoted by D_h(f),
    // Only the truth table is updated. 
    // BE CAREFUL.
    BooleanFun derivative_truth_table_only(int h) const;
   
  private:
    // number of variables
    int n;

    // algebraic degree
    int degree;

    // truth table of this Boolean function, of length 2^n
    // value of f(x_1, x_2, ..., x_n) is truth_table[d(x)],
    // where d(x) := x_1*2^{n-1}+x_2*2^{n-2}+...+x_n.
    int* truth_table;

    // algebraic normal form
    // ANF[d(e)] is the coefficient of x1^{e1}x2^{e2}...xn^{en}.
    int* anf;

    // int array of length 2^n
    // for temp use, used Mobious transform (ANF <-> truth table conversion),
    // and fast fourier transform
    int* tmp;
  
    int* fourier_transform;
  
    // Allocate memory for all pointers, including
    // truth_table, anf, tmp, fourier_transform
    void new_space(int n);

    // Free all space for allocated memory
    void free_space();

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
  
    // Compute the fast_fourier_transform of truth table tt[1<<n], and writes
    // the results into Fourier_arry[1<<n].
    void fast_fourier_transform(int* tt, int* Fourier_arry, int n) const;

    // Returns the base-2 weight of an integer, i.e., returns the
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

    //univariate representation
    //un[i] is delta_i (the coefficient of x^i)
    int* un;
};

#endif
