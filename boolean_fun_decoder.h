#ifndef BOOLEAN_FUN__DECODER_H
#define BOOLEAN_FUN_DECODER_H

#include "affine_trans.h"
#include "boolean_fun.h"

#include <cstdarg>
#include <string>

class BooleanFunDecoder : public BooleanFun {
  public:
    using BooleanFun::BooleanFun;

    //This is super slow
    // only works for n<=5?
    std::vector<BooleanFun> quadratic_list_decoding_brute_force(int d);

    // Returns all codewords with degree at most 2 within (<=) Hamming distance d
    std::vector<BooleanFun> Fourquet_Tavernier_quadratic_list_decoding(int d);

    // Compute the second order nonlinearity using Fourquet-Tavernier list decoding algorithm.
    int second_order_nonlinearity_Fourquet_Tavernier();

  private:

    // For list decoding
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
    void sums(std::vector<BooleanFun>& store, double eps, int v,int m, BooleanFun q_vm1, int* F_vm1);

    // For list decoding algoritm with exit mechanism 
    int sums1(bool &flag,double eps, int v,int m, BooleanFun q_vm1, int* F_vm1);

    // Returns all codewords with degree at most 2 within (<=) Hamming distance d
    int list_decoding_quit(int d);
};

#endif
