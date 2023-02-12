#include"Galois_field_noninit.h"

#include <math.h>
#include <time.h>
#include <cstring>
#include <iostream>

using namespace std;

// IrrPoly calculates an irreducible polynomial in GF(2) with degree n.
void Field_X::IrrPoly() {
	switch (n) {
	case 2:
		irrp = 7;
		this->irrpb = new int[3] {1, 1, 1 };
		break;
	case 3:
		irrp = 11;
		this->irrpb = new int[4] {1, 1, 0, 1 };
		break;
	case 4:
		irrp = 19;
		this->irrpb = new int[5] {1, 1, 0, 0, 1 };
		break;
	case 5:
		irrp = 37;
		this->irrpb = new int[6] {1, 0, 1, 0, 0, 1 };
		break;
	case 6:
		irrp = 67;
		this->irrpb = new int[7] {1, 1, 0, 0, 0, 0, 1 };
		break;
	case 7:
		irrp = 131;
		this->irrpb = new int[8] {1, 1, 0, 0, 0, 0, 0, 1 };
		break;
	case 8:
		irrp = 283;
		this->irrpb = new int[9] {1, 1, 0, 1, 1, 0, 0, 0, 1 };
		break;
	case 9:
		irrp = 515;
		this->irrpb = new int[10] {1, 1, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 10:
		irrp = 1033;
		this->irrpb = new int[11] {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 11:
		irrp = 2053;
		this->irrpb = new int[12] {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 12:
		irrp = 4105;
		this->irrpb = new int[13] {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 13:
		irrp = 8219;
		this->irrpb = new int[14] {1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 14:
		irrp = 16417;
		this->irrpb = new int[15] {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 15:
		irrp = 32771;
		this->irrpb = new int[16] {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 16:
		irrp = 65579;
		this->irrpb = new int[17] {1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 17:
		irrp = 131081;
		this->irrpb = new int[18] {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 18:
		irrp = 262153;
		this->irrpb = new int[19] {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 19:
		irrp = 524327;
		this->irrpb = new int[20] {1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 20:
		irrp = 1048585;
		this->irrpb = new int[21] {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 21:
		irrp = 2097157;
		this->irrpb = new int[22] {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 22:
		irrp = 4194307;
		this->irrpb = new int[23] {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 23:
		irrp = 8388641;
		this->irrpb = new int[24] {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 24:
		irrp = 16777243;
		this->irrpb = new int[25] {1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	case 25:
		irrp = 33554441;
		this->irrpb = new int[26] {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		break;
	default:
		cout << "大于25得重新算哦";
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
		break;
	}
}

// add returns a xor b
int Field_X::add(int a, int b) {
	return a ^ b;
}

// mul returns a*b in Field F2^n.Only used in init Field_X.
int Field_X::mul_init(int a, int b) {
	if (a == 0 || b == 0) {
		return 0;
	}
	int* va = new int[n];
	int* vb = new int[n];
	itob(a, va, n); itob(b, vb, n);
	int* res = new int[2 * n - 1];
	for (int i = 0; i < 2 * n - 1; i++) { res[i] = 0; }
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[i + j] += va[i] * vb[j];
			res[i + j] %= 2;
		}
	}
	div(res, 2 * n - 1, irrpb, n + 1);
	int t = btoi(res, n);
	delete[] va; delete[] vb; delete[] res;
	return t;
}

int Field_X::mul(int a, int b) {
	if (a == 0 || b == 0) {
		return 0;
	}

	// al^i*al^j
	int mul_index = (index_al[a] + index_al[b]) % m;
	return mg[mul_index];
}

// selfMul returns a^k where a is an element in Field F2^n.Only used in init Field_X
int Field_X::selfMul_init(int a, int k) {
	k %= m;
	if (k < 0) {
		k += m;
	}
	int res = 1, t = a;
	while (k > 0) {
		if ((k & 1) == 1) {
			res =  mul_init(res, t);
		}
		t = mul_init(t, t);
		k >>= 1;
	}
	return res;
}

// selfMul returns a^k where a is an element in Field F2^n.
int Field_X::selfMul(int a, int k) {
	k %= m;
	if (k < 0) {
		k += m;
	}
	int res = 1, t = a;
	while (k > 0) {
		if ((k & 1) == 1) {
			res = mul(res, t);
		}
		t = mul(t, t);
		k >>= 1;
	}
	return res;
}

// Ord returns the order of element a.Only used in init Field_X.
int Field_X::ord_init(int a) {
	if (a == 0) {
		return 0;
	}
	int i = 1;
	for (; i <= m; i++) {
		if (m % i != 0) {
			continue;
		}
		if (selfMul_init(a, i) == 1) {
			return i;
		}
	}
	return 1;
}

// Ord returns the order of element a.
int Field_X::ord(int a) {
	if (a == 0) {
		return 0;
	}
	int i = 1;
	for (; i <= m; i++) {
		if (m % i != 0) {
			continue;
		}
		if (selfMul(a, i) == 1) {
			return i;
		}
	}
	return 1;
}


// Pri returns the primitive root in F2^n
void Field_X::Pri() {
	switch (n) {
	case 1:
		this->al = 1;
		return;
	case 2:
		this->al = 2;
		return;
	case 3:
		this->al = 2;
		return;
	case 4:
		this->al = 2;
		return;
	case 5:
		this->al = 2;
		return;
	case 6:
		this->al = 2;
		return;
	case 7:
		this->al = 2;
		return;
	case 8:
		this->al = 26;
		return;
	case 9:
		this->al = 26;
		return;
	case 10:
		this->al = 2;
		return;
	case 11:
		this->al = 2;
		return;
	case 12:
		this->al = 538;
		return;
	case 13:
		this->al = 2;
		return;
	case 14:
		this->al = 8730;
		return;
	case 15:
		this->al = 2;
		return;
	case 16:
		this->al = 25558;
		return;
	case 17:
		this->al = 2;
		return;
	case 18:
		this->al = 124529;
		return;
	case 19:
		this->al = 2;
		return;
	case 20:
		this->al = 2;
		return;
	case 21:
		this->al = 2;
		return;
	case 22:
		this->al = 2;
		return;
	case 23:
		this->al = 2;
		return;
	case 24:
		this->al = 2;
		return;
	case 25:
		this->al = 2;
		return;
	default:
		break;
	}

	// ToDo 优化寻找本原元的算法
	int a = 2, b = 0;                // F2^n里的元素a,b
	int* visited = new int[m + 1];  // 记录已经访问的元素
	for (int i = 0; i <= m; i++) { visited[i] = 0; }
	visited[0], visited[1] = 1, 1;
	srand((int)time(0));
	while (true) {
		//求a的阶以及记录a生成的子群
		int cur = a, i = 1;
		while (cur != 1) {
			visited[cur] = 1;
			//fmt.Printf("a的%d次:%d\n", i-1, cur)
			cur =mul_init(cur, a);
			i++;
		}
		if (i == m) {
			break;
		}

		// 找一个未查询过的元素b
		b = rand() % (m + 1);
		while (visited[b] == 1) {
			b = rand() % (m + 1);
		}
		int j = ord_init(b);
		if (j == m) {
			a = b;
			break;
		}

		// 利用a和b找下一个a
		int g = gcd(i, j);
		a = mul_init(selfMul_init(a, g), b); //a=a^g*b
		if (i * j / gcd(i, j) == m) {
			break;
		}
	}
	delete[] visited;
	al = a;
}

// MulGroup inits the multiple group of F2^n in form of [1,al,al^2...,al^(2^n-2)].
// MulGroup inits the index_al as well.
void Field_X::mulGroup() {
	mg = new int[m];
	index_al = new int[m+1];
	index_al[0] = 0;  //0随便初始化

	mg[0] = 1;
	index_al[1] = 0;
	for (int i = 1; i < m; i++) {
		mg[i] = mul_init(al, mg[i - 1]);
		index_al[mg[i]] = i;
	}
}

Field_X::Field_X(int n) {
	this->n = n;
	this->m = (1 << n) - 1;
	//init the irreducible polynomial
	IrrPoly();
	//init the primitive root al
	Pri();
	//calculate the mulGroup,index_al
	mulGroup();
}

Field_X::~Field_X() {
	delete[] irrpb;
	delete[] mg;
	delete[] index_al;
}

// TruthToUn converts the truth table to uni-variate representation
void TruthToUn(int* truth, int* un, Field_X* f) {
	int n = f->n, m = f->m;
	int* mg = f->mg;
	un[m] = 0;
	for (int i = 0; i < m; i++) {
		int t = 0;
		for (int j = 0; j < m; j++) {
			if (truth[mg[j]] == 1) {
				int p = (-i * j) % m;
				if (p < 0) {
					p += m;
				}
				t = f->add(t, mg[p]);
			}
		}
		un[i] = t;
	}
	int sum = 0;
	for (int i = 0; i < m + 1; i++) {
		sum += truth[i];
	}
	if (sum % 2 != 0) {
		un[0] += 1;
		un[0] %= 2;
		un[m] = 1;
	}
}

// 
bool isBoolean(int* un, Field_X* f) {
	int m = f->m;
	if (un[0] != 0 && un[0] != 1) { return false; }
	if (un[m] != 0 && un[m] != 1) { return false; }
	for (int i = 1; i < m; i++) {
		int j = (2 * i) % m;
		if (un[j] != f->mul(un[i], un[i])) {
			//cout <<"un[j],un[i]="<< un[j]<<","<<un[i] << " " << f->mul(un[i], un[i]) << endl;
			return false;
		}
	}
	return true;
}

// UnToTruth calculates the value in x of the boolean function with un as its uni-variate representation.
void UnToTruth(int* un, int* truth, Field_X* f) {
	int m = f->m;
	truth[0] = un[0];
	for (int x = 1; x < m + 1; x++) {  //当前参数
		int t = 1;
		for (int j = 0; j <= m; j++) {
			truth[x] = f->add(truth[x], f->mul(t, un[j]));
			t = f->mul(x, t); //x^j
		}
	}
}


int Field_X::tr(int x) {
	int res = 0, t = x;
	for (int i = 0; i < n; i++) {
		res = add(res, t);
		t = mul(t, t);
	}
	return res;
}

void Field_X::Tr(int* un, int* truth) {
	UnToTruth(un, truth, this);
	for (int i = 0; i < m + 1; i++) {
		truth[i] = tr(truth[i]);
	}
}

// void UnToTruth(int* un,int* truth,Field_X* f) {
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



