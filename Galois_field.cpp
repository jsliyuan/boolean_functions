#include"Galois_field.h"

#include <math.h>
#include <time.h>
#include <cstring>
#include <iostream>

using namespace std;

// IrrPoly calculates an irreducible polynomial in GF(2) with degree n.
void Field::IrrPoly() {
	this->irrpb = new int[n + 1];
	int lim = 1 << (n / 2 + 1);
	for (int p = m + 1; p < (m + 1) * 2; p++) {
		//p corresponds to a polynomial with degree n
		if (p % 2 == 0) {
			continue;
		}
		int i = 2;
		for (; i < lim; i++) {
			if (isDivisible(p, i, n)) {
				break;
			}
		}
		if (i == lim) {
			this->irrp = p;
			itob(p, irrpb, n + 1);
			return;
		}
	}
}

// add returns a xor b
int Field::add(int a,int b){
	return a^b;
}

// mul returns a*b in Field F2^n
int Field:: mul(int a,int b)  {
	if (a == 0 || b == 0) {
		return 0;
	}
	int *va=new int[n];
	int *vb=new int[n];
	itob(a,va,n);itob(b,vb,n);
	int *res=new int[2*n-1];
	for(int i=0;i<2*n-1;i++){res[i]=0;}
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			res[i+j]+=va[i]*vb[j];
			res[i+j]%=2;
		}
	}
	div(res,2*n-1,irrpb,n+1);
	int t=btoi(res,n);
	delete[] va;delete[] vb;delete[] res;
	return t;
}

// selfMul returns a^k where a is an element in Field F2^n.
int Field:: selfMul(int a,int k){
	k %= m;
	if (k < 0) {
		k += m;
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
	for (; i <= m; i++) {
		if (m%i != 0) {
			continue;
		}
		if (selfMul(a,i) == 1) {
			return i;
		}
	}
	return 1;
}

// Pri returns the primitive root in F2^n
void Field:: Pri() {
	if (n == 1) {
		al = 1;
		return;
	}
	// ToDo 优化寻找本原元的算法
	int a=2,b=0;                // F2^n里的元素a,b
	int* visited=new int[m+1];  // 记录已经访问的元素
	for(int i=0;i<=m;i++){visited[i]=0;}
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
		if (i == m) {
			break;
		}

		// 找一个未查询过的元素b
		b = rand()%(m+1);
		while (visited[b] == 1) {
			b = rand()%(m + 1);
		}
		int j=ord(b);
		if (j == m) {
			a = b;
			break;
		}

		// 利用a和b找下一个a
		int g = gcd(i, j);
		a = mulTab[selfMul(a, g)][b]; //a=a^g*b
		if (i*j/gcd(i, j) == m) {
			break;
		}
	}
	delete[] visited;
	al = a;
}

// MulGroup inits the multiple group of F2^n in form of [1,al,al^2...,al^(2^n-2)]
void Field:: mulGroup() {
	mg = new int[m];
	mg[0] = 1;
	for (int i = 1; i < m; i++) {
		mg[i] = mulTab[al][mg[i - 1]];
	}
}

void Field::initTab() {
	mulTab = new int* [1 << n];
	addTab = new int* [1 << n];
	for (int i = 0; i < 1 << n; i++) {
		mulTab[i] = new int[1 << n];
		addTab[i] = new int[1 << n];
	}
	//calculate the mulTable,addTab
	//cout << "need init table" << endl;
	for (int i = 0; i < 1 << n; i++) {
		mulTab[i][i] = mul(i, i);
		addTab[i][i] = 0;
		for (int j = i + 1; j < 1 << n; j++) {
			mulTab[j][i] = mulTab[i][j] = mul(i, j);
			addTab[j][i] = addTab[i][j] = add(i, j);
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

////init the Field without initialization.
//Field::Field(int n,bool useTable=false) {
//	this->n = n;
//	this->m = (1 << n) - 1;
//	this->useTable = useTable;
//	IrrPoly();
//	mulTab = new int* [1<<n];   // 为啥这个初始化长度不是这个会报错
//	addTab = new int* [1<<n];
//	for (int i = 0; i < 1<<n; i++) {
//		mulTab[i] = NULL;
//		addTab[i] = NULL;
//	}
//	Pri();
//	mulGroup();
//}

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
void TruthToUn(int* truth,int* un,Field* f) {
	int n=f->n,m=f->m;
	int* mg=f->mg;
	un[m]=0;
	for (int i = 0; i < m; i++) {
		int t=0;
		for (int j = 0; j < m; j++) {
			if (truth[mg[j]] == 1) {
				int p = (-i * j) % m;
				if (p < 0) {
					p += m;
				}
				t = f->addTab[t][mg[p]];
			}
		}
		un[i] = t;
	}
	int sum=0;
	for (int i=0;i<m+1;i++){
		sum+=truth[i];
	}
	if (sum%2 != 0) {
		un[0] += 1;
		un[0] %= 2;
		un[m] = 1;
	}
}

// 
bool isBoolean(int* un,Field* f){
	int m=f->m;
	if(un[0]!=0&&un[0]!=1){return false;}
	if(un[m]!=0&&un[m]!=1){return false;}
	for (int i=1;i<m;i++){
		int j=(2*i)%m;
		if (un[j]!=f->mulTab[un[i]][un[i]]) {
			return false;
		}
	}
	return true;
}

// UnToTruth calculates the value in x of the boolean function with un as its uni-variate representation.
void UnToTruth(int* un,int* truth,Field* f) {
	int m=f->m;
	truth[0]=un[0];
	for (int x=1;x<m+1;x++){  //当前参数
		int t=1;
		for (int j= 0; j <= m; j++) {
			truth[x] = f->add(truth[x], f->mulTab[t][un[j]]);
			t = f->mulTab[x][t]; //x^j
		}
	}
}


int Field::tr(int x){
	int res=0,t=x;
	for(int i=0;i<n;i++){
		res=addTab[res][t];
		t=mulTab[t][t];
	}
	return res;
}

void Field::Tr(int* un,int *truth){
	UnToTruth(un,truth,this);
	for (int i=0;i<m+1;i++){
		truth[i]=tr(truth[i]);
	}
}

// void UnToTruth(int* un,int* truth,Field* f) {
// 	int n=f->n,m=f->m;
// 	vector<int> basis(n); //一组基
// 	basis[0] = 1;
// 	for (int i = 1; i < n; i++) {
// 		basis[i] = basis[i-1] * 2;
// 	}
// 	vector<vector<vector<int>>> baspow(n,vector<vector<int>>(n));  
// 	for (int i = 0; i < n; i++) {
// 		baspow[i][0] = itob(basis[i]);
// 		for (int j = 1; j < n; j++) {
// 			baspow[i][j] = f->selfMul(baspow[i][j-1], 2);
// 		}
// 	}
// 	vector<vector<int>> unv(m+1);
// 	for (int i=0;i<m+1;i++){
// 		unv[i]=itob(un[i]);
// 	}
// 	truth[0]=un[0];
// 	for (int x=1;x<m+1;x++){
// 		vector<int> res;
// 		vector<int> vx=itob(x);
// 		for (int k=0;k<m+1;k++){
// 			vector<int> t={1};
// 			vector<int> vk=itob(k);
// 			for (int i=0;i<vk.size();i++){
// 				if (vk[i]==0){continue;}
// 					vector<int> d;
// 					for (int j=0;j<vx.size();j++){
// 						if (vx[j]==0){continue;}
// 						d=f->add(d,baspow[j][i]);
// 					}
// 					t=f->mul(t,d);
// 			}
// 			t=f->mul(t,unv[k]);
// 			res=f->add(res,t);
// 		}
// 		truth[x]=btoi(res);
// 	}
// }



