#include"Galois_field.h"

#include <math.h>
#include <time.h>
#include <cstring>
#include <iostream>

using namespace std;

// IrrPoly calculates an irreducible polynomial in GF(2) with degree n.
void Field::IrrPoly() {
	this->irrpb = new int[this->n + 1];
	int lim = 1 << (this->n / 2 + 1);
	for (int p = this->m + 1; p < (this->m + 1) * 2; p++) {
		//p corresponds to a polynomial with degree n
		if (p % 2 == 0) {
			continue;
		}
		int i = 2;
		for (; i < lim; i++) {
			if (this->isDivisible(p, i, this->n)) {
				break;
			}
		}
		if (i == lim) {
			this->irrp = p;
			this->itob(p, this->irrpb, this->n + 1);
			return;
		}
	}
}

// add returns a xor b
int Field::add(int a,int b){
	return a ^ b;
}

int Field::sub(int a, int b) {
	return a ^ b;
}

// mul returns a*b in Field F2^n
int Field:: mul(int a,int b)  {
	if (a == 0 || b == 0) {
		return 0;
	}
	int *va=new int[this->n];
	int *vb=new int[this->n];
	this->itob(a, va, this->n);
	this->itob(b, vb, this->n);
	int *res=new int[2*this->n - 1];
	for(int i=0; i < 2*this->n-1; i++){
		res[i]=0;}
	for (int i=0; i < this->n; i++){
		for (int j=0; j < this->n; j++){
			res[i+j]+=va[i]*vb[j];
			res[i+j]%=2;
		}
	}
	module(res,2*this->n - 1,this->irrpb, this->n+1);
	int t=this->btoi(res, this->n);
	delete[] va;
	delete[] vb;
	delete[] res;
	
	return t;
}

int Field::div(int a, int b) {
	return this->mulTab[a][this->inv(b)];
}

// selfMul returns a^k where a is an element in Field F2^n.
int Field:: selfMul(int a,int k){
	k %= this->m;
	if (k < 0) {
		k += this->m;
	}
	int res=1,t=a;
	while (k > 0) {
		if ((k & 1) == 1) {
			res = mulTab[res][t];
		}
		t = mulTab[t][t];
		k >>= 1;
	}
	return res;
}

// Ord returns the order of element a
int Field:: ord(int a) {
	if (a == 0) {
		return 0;
	}
	int i=1;
	for (; i <= this->m; i++) {
		if (this->m%i != 0) {
			continue;
		}
		if (this->selfMul(a,i) == 1) {
			return i;
		}
	}
	return 1;
}

// return the inverse element of a
int Field::inv(int a) {
	if (a == 1) {
		return 1;
	}
	return this->selfMul(a, this->m - 1);
}

// Pri returns the primitive root in F2^n
void Field:: Pri() {
	if (this->n == 1) {
		this->al = 1;
		return;
	}
	// ToDo 优化寻找本原元的算法
	int a=2, b=0;                // F2^n里的元素a,b
	int* visited = new int[this->m+1];  // 记录已经访问的元素
	for(int i = 0 ; i <= this->m ; i++) {
		visited[i]=0;
	}
	visited[0],visited[1] = 1, 1;
	srand((int)time(0));

	while (true) {
		//求a的阶以及记录a生成的子群
		int cur=a,i=1;
		while (cur!=1) {
			visited[cur] = 1;
			//fmt.Printf("a的%d次:%d\n", i-1, cur)
			cur = mulTab[cur][a];
			i++;
		}
		if (i == this->m) {
			break;
		}

		// 找一个未查询过的元素b
		b = rand()%(this->m+1);
		while (visited[b] == 1) {
			b = rand()%(this->m + 1);
		}
		int j=this->ord(b);
		if (j == this->m) {
			a = b;
			break;
		}

		// 利用a和b找下一个a
		int g = this->gcd(i, j);
		a = mulTab[this->selfMul(a, g)][b]; //a=a^g*b
		if (i*j/this->gcd(i, j) == this->m) {
			break;
		}
	}
	delete[] visited;
	this->al = a;
}

// MulGroup inits the multiple group of F2^n in form of [1,al,al^2...,al^(2^n-2)]
void Field:: mulGroup() {
	this->mg = new int[this->m];
	mg[0] = 1;
	for (int i = 1; i < this->m; i++) {
		mg[i] = mulTab[al][mg[i - 1]];
	}
}

void Field::initTab() {
	mulTab = new int* [1 << this->n];
	addTab = new int* [1 << this->n];
	for (int i = 0; i < 1 << this->n; i++) {
		mulTab[i] = new int[1 << this->n];
		addTab[i] = new int[1 << this->n];
	}
	//calculate the mulTable,addTab
	//cout << "need init table" << endl;
	for (int i = 0; i < 1 << this->n; i++) {
		mulTab[i][i] = this->mul(i, i);
		addTab[i][i] = 0;
		for (int j = i + 1; j < 1 << this->n; j++) {
			mulTab[j][i] = mulTab[i][j] = this->mul(i, j);
			addTab[j][i] = addTab[i][j] = this->add(i, j);
		}
	}
}

Field::Field(int n) {
	this->n = n;
	this->m = (1 << n) - 1;
	IrrPoly();
	cout << "IrrPoly ok" << endl;
	initTab();
	cout << "initTab ok" << endl;
	//init the primitive root al
	Pri();
	cout << "Pri ok" << endl;
	//calculate the mulGroup
	mulGroup();
}


Field::~Field() {
	delete[] irrpb;
	delete[] mg;
	for (int i = 0; i < 1 << n; i++) {
		delete[] mulTab[i];
		delete[] addTab[i];
	}
	delete[] mulTab;
	delete[] addTab;
}

// TruthToUn converts the truth table to uni-variate representation
void Field::TruthToUn(int* truth,int* un) {
	int num=this->n, order=this->m;
	int* term=this->mg;
	un[order]=0;
	for (int i = 0; i < order; i++) {
		int t=0;
		for (int j = 0; j < order; j++) {
			if (truth[term[j]] == 1) {
				int p = (-i * j) % order;
				if (p < 0) {
					p += order;
				}
				t = this->addTab[t][term[p]];
			}
		}
		un[i] = t;
	}
	int sum=0;
	for (int i=0; i<order+1; i++){
		sum+=truth[i];
	}
	if (sum%2 != 0) {
		un[0] += 1;
		un[0] %= 2;
		un[order] = 1;
	}
}

// 
bool Field::isBoolean(int* un){
	int order=this->m;
	if(un[0]!=0&&un[0]!=1) {
		return false;}
	if(un[order]!=0 && un[order]!=1) {
		return false;}
	for (int i=1; i<order; i++){
		int j=(2*i)%order;
		if (un[j]!=this->mulTab[un[i]][un[i]]) {
			return false;
		}
	}
	return true;
}

// UnToTruth calculates the value in x of the boolean function with un as its uni-variate representation.
void Field::UnToTruth(int* un,int* truth) {
	int order=this->m;
	truth[0]=un[0];
	for (int x=1;x<order+1;x++){  //当前参数
		int t=1;
		for (int j= 0; j <= order; j++) {
			truth[x] = this->add(truth[x], this->mulTab[t][un[j]]);
			t = this->mulTab[x][t]; //x^j
		}
	}
}


int Field::tr1(int x){
	int res=0,t=x;
	for(int i=0; i<this->n; i++){
		res=addTab[res][t];
		t=mulTab[t][t];
	}
	return res;
}

void Field::Tr(int* un,int *truth){
	this->UnToTruth(un,truth);
	for (int i=0 ; i<m+1; i++){
		truth[i]=this->tr1(truth[i]);
	}
}

// itob converts int to binary array,
// which is arranged from low level.
void Field::itob(int x, int* p, int num) {
	for (int i = 0; i < num; i++) {
		if (x > 0) {
			p[i] = x % 2;
			x /= 2;
		}
		else {
			p[i] = 0;
		}
	}
}

// btoi converts binary array to int.
int Field::btoi(int* b, int num) {
	int res = 0, t = 1;
	for (int i = 0; i < num; i++) {
		res += b[i] * t;
		t *= 2;
	}
	return res;
}

void Field::module(int* va, int la, int* vb, int lb) {
	int pa, pb;  
	for (pa = la - 1; pa >= 0; pa--) {
		if (va[pa] != 0) { break; }
	}
	for (pb = lb - 1; pb >= 0; pb--) {
		if (vb[pb] != 0) { break; }
	}
	while (pa >= pb) {
		//printf("current pa:%d,pb:%d\n",pa,pb);
		int p = -1;  
		for (int i = 0; i <= pb; i++) {
			va[pa - i] ^= vb[pb - i];
			if (va[pa - i] == 1 && p == -1) {
				p = pa - i;
			}
		}
		pa = p != -1 ? p : pa - pb - 1;
	}
}

// IsDivisible decides that whether g can be divided by f in Field F_2.
bool Field::isDivisible(int a, int b, int num) {
	int* va = new int[num + 1];
	int* vb = new int[num];
	this->itob(a, va, num + 1); 
	this->itob(b, vb, num);
	this->module(va, num + 1, vb, num);
	bool res = (this->btoi(va, num) == 0);
	delete[] va; 
	delete[] vb;
	return res;
}

int Field::gcd(int x, int y) {
	int tem;
	while (y != 0) {
		tem = y;
		x = y; y = tem % y;
	}
	return x;
}

// get all private parameters

// return the size of field
int Field::get_varnum() {
	return this->n;
}

// return the multiple group's order
int Field::get_order() {
	return m;
}

//return the irreducible polynomial
int Field::get_irrp() {
	return irrp;
}

//return the binary representation of irrp
const int* Field::get_irrpb() {
	return irrpb;
}

// return the primitive root
int Field::get_root() {
	return al;
}

// return [1,al,al^2,...,al^(2^n-2)]
const int* Field::get_root_list() {
	return mg;
}

// return the multiple table
int** Field::get_mul_table() {
	return mulTab;
}

// return the addtional table
int** Field::get_add_table() {
	return addTab;
}



