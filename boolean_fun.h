#include <cstdarg>
#include <string>

class BooleanFun {
  public:
    // Returns the number of variables.
    int var_num();

    // Constructor with parameter (number of variables)
    // Create an all-zero Boolean function in n variables.
    BooleanFun(int n);

    // Constructor with parameters, where n is the number
    // of variables, and anf is the algebraic normal form.
    // If anf is invalid, we throw an exception.
    // For example,
    // "0": the all-0 Boolean function
    // "1": the all-1 Boolean function
    // "x1*x2+1": x1*x2+1
    // "x1*x2+x4*x5": x1*x2+x4*x5
    // We do not support parenthesis "()" for now.
    BooleanFun(int n, std::string anf_str);

    // Destructor
    ~BooleanFun();

    // Evaluate boolean function at a given point.
    // We must have num = n; otherwise returns -1.
    int value(int num, ...);

  private:
    // number of variables
    int n;

    // truth table of this Boolean function, of length 2^n
    // value of f(x_1, x_2, ..., x_n) is truth_table[d(x)],
    // where d(x) := x_1+x_2*2+...+x_n*2^{n-1}.
    int* truth_table;

    // algebraic normal form
    // ANF[d(e)] is the coefficient of x1^{e1}x2^{e2}...xn^{en}.
    int* anf;

    // Compute truth table from anf.
    void anf_to_truth_table();

    // Returns the decimal representation of the given term.
    // Example terms: "x1x2x3", "x3x11".
    // Each term is of the form x^a = x1^{a1}x2^{a2}...xn^{an},
    // where a is in {0,1}^n
    // Returns the decimal value of the binary number (a1, a2, ..., an).
    int get_term(std::string term);
};
