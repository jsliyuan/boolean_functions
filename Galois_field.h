
#include <vector>

using namespace std;

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

