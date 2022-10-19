/*  BooleanFunDecoder is an inheritance of BooleanFun class.
We implement a more fast algorithm to calculate the second-order nonlinearity
of Boolean function in n variables (n<=12), according to Fourquet_Tavernier list decoding algorithm
for second-order nonlinearity. The algorihtm is in the Fourquet-Tavernier paper.
https://link.springer.com/content/pdf/10.1007/s10623-008-9184-8.pdf.

Moreover, calculating the list of all codewords with degree at most 2 
within (<=) Hamming distance d from the Boolean function can be implemented in
the function, denoted by Fourquet_Tavernier_quadratic_list_decoding(d).
For contrast, we also implement a brute force search method which is super slow
and may only work for n<=5.
*/

#ifndef BOOLEAN_FUN__DECODER_H
#define BOOLEAN_FUN_DECODER_H

#include "affine_trans.h"
#include "boolean_fun.h"

#include <cstdarg>
#include <string>

class BooleanFunDecoder : public BooleanFun {
  public:
    using BooleanFun::BooleanFun;

    //Brute_force searching is super slow
    // only works for n<=5?
    std::vector<BooleanFun> quadratic_list_decoding_brute_force(int d);

    // Returns all codewords with degree at most 2 within (<=) Hamming distance d
    // It is much faster than the brute_force searching
    std::vector<BooleanFun> Fourquet_Tavernier_quadratic_list_decoding(int d);

    // Compute the second order nonlinearity using Fourquet-Tavernier list decoding algorithm.
    int second_order_nonlinearity_Fourquet_Tavernier();

  private:

    // Get the initial F_v as input
    // The algorihtm is in the Fourquet-Tavernier paper.
    int initial_Fv(int* &F_v, int m, int v, BooleanFun q_v);

    // Compute M for all Q_v in [0, 2^(v-1))
    // The algorihtm is in the Fourquet-Tavernier paper.
    int compute_M(int* F_vm1, int v, int m,int s, int Q_v);

    // Compute M fast for all Q_v in [0, 2^(v-1))
    // The algorihtm is in the Fourquet-Tavernier paper.
    void compute_M_fast(int* F_vm1, int v, int m, int s, int* M);

    // Compute F_v from F_vm1 for all Q_v in [0, 2^(v-1))
    int compute_Fv(int* &F_v, int* F_vm1, int Q_v,int m,int v);

    // For list decoding algoritm
    // The algorihtm is in the Fourquet-Tavernier paper.
    void sums(std::vector<BooleanFun>& store, double eps, int v,int m, BooleanFun q_vm1, int* F_vm1);

    // For list decoding algoritm with exit mechanism 
    // The algorihtm is in the Fourquet-Tavernier paper.
    int sums1(bool &flag,double eps, int v,int m, BooleanFun q_vm1, int* F_vm1);

    // Returns all codewords with degree at most 2 within (<=) Hamming distance d
    int list_decoding_quit(int d);
};

#endif
