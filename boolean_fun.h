#include <cstdarg>

class BooleanFun {
  public:
    int var_num();

    // Constructor with parameter (number of variables)
    // Create an all-zero Boolean function in n variables.
    BooleanFun(int n);

    // Destructor
    ~BooleanFun();

    // Evaluate boolean function at a given point.
    // We must have num = n; otherwise returns -1.
    int value(int num, ...);
  private:
    bool* truth_table; // truth table of this Boolean function, of length 2^n
    int n;        // number of variables
};

