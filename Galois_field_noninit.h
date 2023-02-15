#ifndef GALOIS_FIELD_NONINIT_H
#define GALOIS_FIELD_NONINIT_H

class Field_X {
public:

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

	int tr1(int x);   //calculate the tr_n of x

	void Tr(int* un, int* truth);  //calculate the truth_table of tr_n(f),the univariate coefficients of f is un

	// TruthToUn converts the truth table to uni-variate representation
	void TruthToUn(int* truth, int* un);

	bool isBoolean(int* un);

	// UnToTruth calculates the value in x of the boolean function with un as its uni-variate representation.
	void UnToTruth(int* un, int* truth);

	// itob converts int to binary array,
	// which is arranged from low level.
	void itob(int x, int* p, int n);
	//
	// btoi converts binary array to int.
	int btoi(int* b, int n);
	//
	void div(int* va, int la, int* vb, int lb);
	//
	// IsDivisible decides that whether g can be divided by f in Field F_2.
	bool isDivisible(int a, int b, int n);
	
	int gcd(int x, int y);

	// get all private parameters
	int get_varnum();

	int get_order();

	int get_irrp();

	const int* get_irrpb();

	int get_root();

	const int* get_root_list();

	const int* get_index_al();

private:
	int n;  //2^n
	int m; //multiple group's order
	int irrp;  //a irreducible polynomial of degree n
	int* irrpb;  //binary representation of irrp
	int al ;  //primitive root
	int* mg;  //[1,al,al^2,...,al^(2^n-2)]
	int* index_al; //记录一个元素是al的几次方;index_al[t]=k表示t=al^k
};



#endif // !GALOIS_FIELD_NONINIT_H
