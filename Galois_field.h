#ifndef GALOIS_FIELD_H
#define GALOIS_FIELD_H

class Field{
public:

	Field(int n);                //init the Tab

	//Field(int n,bool useTable);  //init the Field without Tab(at least 13)

	~Field();

	void initTab();

	void IrrPoly();  //calculate the irreducible polynomial

	int add(int a, int b);	//a+b

	int sub(int a, int b);  //a-b

	int mul(int a, int b);	//a*b

	int div(int a, int b);	//a÷b

	int selfMul(int a,int k);  //a^k

	int ord(int a);  //the order of a

	void Pri();  //calculate the primitive root

	int inv(int a);  //the inverse element of a

	void mulGroup();  // MulGroup inits the multiple group of F2^n in form of [1,al,al^2...,al^(2^n-2)]

	int tr1(int x);   //calculate the tr_n of x

	void Tr(int* un,int* truth);  //calculate the truth_table of tr_n(f),the univariate coefficients of f is un

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
	void module(int* va, int la, int* vb, int lb);
	//
	// IsDivisible decides that whether g can be divided by f in Field F_2.
	bool isDivisible(int a, int b, int n);
	
	int gcd(int x, int y);

	// get all private parameters

	// return the size of field
	int get_varnum();

	// return the multiple group's order
	int get_order();

	//return the irreducible polynomial
	int get_irrp();

	//return the binary representation of irrp
	const int* get_irrpb();

	// return the primitive root
	int get_root();

	//return [1,al,al^2,...,al^(2^n-2)]
	const int* get_root_list();

	// return the multiple table
	int** get_mul_table();

	// return the addtional table
	int** get_add_table();

private:
	int n;  //2^n
	int m; //multiple group's order
	int irrp;  //a irreducible polynomial of degree n
	int* irrpb;  //binary representation of irrp
	int al;  //primitive root
	int* mg;  //[1,al,al^2,...,al^(2^n-2)]
	int** mulTab;  //multiple table
	int** addTab;  //addition table(可以考虑去了，性能没增加多少内存多了一倍)
};


#endif // !GALOIS_FIELD_H