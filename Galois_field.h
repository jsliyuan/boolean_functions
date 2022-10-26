#ifndef GALOIS_FIELD_H
#define GALOIS_FIELD_H

using namespace std;

// itob converts int to binary array,
// which is arranged from low level.
void itob(int x, int* p, int n);

// btoi converts binary array to int.
int btoi(int* b, int n);

void div(int* va, int la, int* vb, int lb);

// IsDivisible decides that whether g can be divided by f in Field F_2.
bool isDivisible(int a, int b, int n);

int gcd(int x, int y);


class Field{
public:
	int n;  //2^n
	int m; //multiple group's order
	int irrp;  //a irreducible polynomial of degree n
	int* irrpb;  //binary representation of irrp
	int al;  //primitive root

	Field(int n);

	void IrrPoly();  //calculate the irreducible polynomial

	int add(int a,int b);

	int mul(int a,int b);

	int selfMul(int a,int k);  //a^k

	int ord(int a);  //the order of a

	void Pri();  //calculate the primitive root

	int* mulGroup();  //return [1,al,al^2,...,al^(2^n-2)]

	int tr(int x);   //calculate the tr_n of x

	void Tr(int* un,int* truth);  //calculate the truth_table of tr_n(f),the univariate coefficients of f is un
};

// TruthToUn converts the truth table to uni-variate representation
void TruthToUn(int* truth, int* un, Field* f);

bool isBoolean(int* un, Field* f);

// UnToTruth calculates the value in x of the boolean function with un as its uni-variate representation.
void UnToTruth(int* un, int* truth, Field* f);

#endif // !GALOIS_FIELD_H