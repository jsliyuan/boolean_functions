#include <string>

// Affine transformation Ax + b: GF(2)^n -> GF(2)^n,
// where A is an n*n matrix, and b is an n*1 array.
class AffineTrans {
  public:
    // Constructor with parameter (dimension).
    // Create an all-zero affine transformation.
    AffineTrans(int n);

    // Constructor with parameters n, A and b.
    AffineTrans(int n, int* A, int* b);

    // Returns Ax + b, where both x and the result
    // is in the decimal representation.
    // Point (x1, x2, ..., xn) is represented by
    // x := x_1*2^{n-1}+x_2*2^{n-2}+...+x_n.
    // Returns -1 if x out of range [0, 2^n-1]
    int apply(int x) const;

    // Let A[i][j] = v, where 1 <= i, j <= n.
    // If i or j is out of range, returns false.
    bool set_a(int i, int j, int v);

    // Let b[i] = v, where 1 <= i <= n.
    // If i is out of range, returns false.
    bool set_b(int i, int v);

    // Gets A[i][j], where 1 <= i, j <= n.
    // Returns -1 if i or j is out of range.
    int get_a(int i, int j) const;

    // Gets b[i], where 1 <= i <= n.
    // Returns -1 if i is out of range.
    int get_b(int i) const;

    // Returns the dimension n.
    int get_n() const;

    // Returns a as n*n matrix in string, for example,
    // 1 0 1\n
    // 0 1 0\n
    // 0 0 1
    std::string get_a_str() const;

    // Returns b as vector, for example,
    // 1 0 1
    std::string get_b_str() const;

    // Let this = this * T, where T is applied first, i.e.,
    // this(T(x))
    // bool compose(const AffineTrans& T);

    // Let this = T * this, where this is applied first, i.e.,
    // T(this(x))
    // bool compose_last(const AffineTrans& T);

  private:
    // dimension
    int n;

    // n*n matrix
    // (i, j) maps to (i-1)*n+(j-1), where i, j in [1,n]
    int* A;

    // n*1 array
    int* b;
};
