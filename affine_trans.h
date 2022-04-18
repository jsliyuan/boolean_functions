#ifndef AFFINE_TRANS_H
#define AFFINE_TRANS_H

#include <string>
#include <unordered_set>

// Affine transformation Ax + b: GF(2)^n -> GF(2)^n,
// where A is an n*n matrix, and b is an n*1 array.
class AffineTrans {
  public:
    // Constructor with parameter (dimension).
    // Create an all-zero affine transformation.
    AffineTrans(int n);

    // Constructor with parameters n, A and b.
    AffineTrans(int n, int* A, int* b);

    // Copy constructor.
    // Performs a deep copy.
    AffineTrans(const AffineTrans& T);

    // Constructor with n and (A, b) in string format, e.g.,
    // [100000 010000 001000 000100 000010 000001]100000
    AffineTrans(int n, std::string str);

    // Destructor.
    ~AffineTrans();

    // Assignment operator
    AffineTrans& operator=(const AffineTrans& T);

    // Returns Ax + b, where both x and the result
    // is in the decimal representation.
    // Point (x1, x2, ..., xn) is represented by
    // x := x_1*2^{n-1}+x_2*2^{n-2}+...+x_n.
    // Returns -1 if x out of range [0, 2^n-1]
    int apply(int x) const;

    // Given a string, set A, b. E.g.,
    // [100000 010000 001000 000100 000010 000001]100000
    // Returns false if there are less than n*(n+1) 0 or 1.
    bool set_ab(std::string str);

    // Let A[i][j] = v, where 1 <= i, j <= n.
    // If i or j is out of range, returns false.
    bool set_a(int i, int j, int v);

    // Set the entire row i, where v is the decimial representation
    // of (A[i][n], A[i][n-1], ..., A[i][1])_2.
    // If i or v is out of range, returns false.
    bool set_row_a(int i, int v);

    // Set the matrix randomly, and make sure it is nonsingular, i.e.,
    // determinant is 1.
    void set_random();

    // Set the vector b randomly.
    void set_random_b();

    // Let b[i] = v, where 1 <= i <= n.
    // If i is out of range, returns false.
    bool set_b(int i, int v);

    // Gets A[i][j], where 1 <= i, j <= n.
    // Returns -1 if i or j is out of range.
    int get_a(int i, int j) const;

    // Gets A[i][1], A[i][2], ..., A[i][n] as an integer
    // A[i][1] + A[i][2]*2 + ... + A[i][n]*2^{n-1}
    // in range [0, 2^n-1].
    // Returns -1 if i is not in [1, n].
    int get_a_row(int i) const;

    // Gets b[i], where 1 <= i <= n.
    // Returns -1 if i is out of range.
    int get_b(int i) const;

    // Returns the dimension n.
    int get_n() const;

    // Returns A and b in string format, e.g.,
    // [100000 010000 001000 000100 000010 000001]100000
    std::string get_ab_str() const;

    // Returns a as n*n matrix in string, for example,
    // 1 0 1\n
    // 0 1 0\n
    // 0 0 1
    std::string get_a_str() const;

    // Returns b as vector, for example,
    // 1 0 1
    std::string get_b_str() const;

    // Return the span of the row vectors (a_i, a_{i+1}, ..., a_j).
    // Each vector is represented as an integer in the natural way,
    // and returns a set of integers of size 2^k, where 0 <= k <= j-i+1.
    // Vector v = (v1, v2, ..., vn) is represented by integer
    // v1 + v2*2 + v3*4 + ... + vn*2^{n-1}.
    std::unordered_set<int>  get_rows_span(int i, int j) const;

    // Let this = this * T, where T is applied first, i.e.,
    // this(T(x)) = this(T.Ax + T.b)
    //            = A*T.Ax + A*T.b + T.b
    // Returns false if the dimension does not match.
    bool mult(const AffineTrans& T);

    // Returns the determinant of A, which is 0 or 1.
    int det() const;

    // Let A := A^{-1}.
    // If A is not invertible, returns false.
    bool inverse();

    // ACCESS TO MEMBER VARIABLE. BE CAREFUL!
    // n*n matrix
    // (i, j) maps to (i-1)*n+(j-1), where i, j in [1,n]
    int* A;

    // ACCESS TO MEMBER VARIABLE. BE CAREFUL!
    // n*1 array
    int* b;

  private:
    // dimension
    int n;

    // Allocate memory and copies all data from T to this.
    void copy_data(const AffineTrans& T);

    // Helper function, matrix multplication
    // n is the dimension, and dest = M1*M2
    // M[i][j] -> M[(i-1)*n + (j-1)]
    void matrix_mult(int n, int* dest, int* M1, int* M2);

    // Helper function, matrix * vector of dimension n
    // dest = A*b
    // A[i][j] -> A[(i-1)*n + (j-1)]
    void matrix_vec_mult(int n, int *dest, int* A, int* b);
};

#endif
