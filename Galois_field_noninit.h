#ifndef GALOIS_FIELD_NONINIT_H
#define GALOIS_FIELD_NONINIT_H

#include"Galois_field_util.h"

using namespace std;

class Field_X {
public:
	int n;  //2^n
	int m; //multiple group's order
	int irrp;  //a irreducible polynomial of degree n
	int* irrpb;  //binary representation of irrp
	int al = 0;  //primitive root
	int* mg;  //[1,al,al^2,...,al^(2^n-2)]
	int* index_al; //记录一个元素是al的几次方;index_al[t]=k表示t=al^k

	Field_X(int n);                //init Field_X

	~Field_X();

	void IrrPoly();  //calculate the irreducible polynomial

	int add(int a, int b);

	int mul_init(int a, int b); // Only used in init Field_X.

	int selfMul_init(int a, int k);  //a^k;Only used in init Field_X.

	int ord_init(int a);  //the order of a ;Only used in init Field_X.

	int mul(int a, int b);

	int selfMul(int a, int k);  //a^k

	int ord(int a);  //the order of a

	void Pri();  //calculate the primitive root

	void mulGroup();  // MulGroup inits the multiple group of F2^n in form of [1,al,al^2...,al^(2^n-2)],index_al.

	int tr(int x);   //calculate the tr_n of x

	void Tr(int* un, int* truth);  //calculate the truth_table of tr_n(f),the univariate coefficients of f is un
};

// TruthToUn converts the truth table to uni-variate representation
void TruthToUn(int* truth, int* un, Field_X* f);

bool isBoolean(int* un, Field_X* f);

// UnToTruth calculates the value in x of the boolean function with un as its uni-variate representation.
void UnToTruth(int* un, int* truth, Field_X* f);

#endif // !GALOIS_FIELD_NONINIT_H