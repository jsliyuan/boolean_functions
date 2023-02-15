#include "Galois_field_noninit.h"

#include <math.h>
#include <time.h>
#include <cstring>
#include <iostream>

using namespace std;

// MulGroup inits the multiple group of F2^n in form of [1,al,al^2...,al^(2^n-2)].
// MulGroup inits the index_al as well.
void Field_X::mulGroup() {
	this->mg = new int[this->m];
	this->index_al = new int[this->m + 1];
	index_al[0] = 0;  //

	mg[0] = 1;
	index_al[1] = 0;
	for (int i = 1; i < m; i++) {
		mg[i] = this->mul_init(al, mg[i - 1]);
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


// IrrPoly calculates an irreducible polynomial in GF(2) with degree n.
void Field_X::IrrPoly() {
	switch (this->n) {
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
		cout << "need to redefine: ";
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
				this->itob(p, irrpb, this->n + 1);
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
	int* va = new int[this->n];
	int* vb = new int[this->n];
	this->itob(a, va, this->n); 
	this->itob(b, vb, this->n);
	int* res = new int[2 * (this->n) - 1];
	for (int i = 0; i < 2 * (this->n) - 1; i++) { res[i] = 0; }
	for (int i = 0; i < (this->n); i++) {
		for (int j = 0; j < (this->n); j++) {
			res[i + j] += va[i] * vb[j];
			res[i + j] %= 2;
		}
	}
	this->div(res, 2 * (this->n) - 1, this->irrpb, (this->n) + 1);
	int t = this->btoi(res, this->n);
	delete[] va; 
	delete[] vb; 
	delete[] res;
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
			res =  this->mul_init(res, t);
		}
		t = this->mul_init(t, t);
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
			res = this->mul(res, t);
		}
		t = this->mul(t, t);
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
		if (this->selfMul_init(a, i) == 1) {
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
	for (; i <= this->m; i++) {
		if (this->m % i != 0) {
			continue;
		}
		if (this->selfMul(a, i) == 1) {
			return i;
		}
	}
	return 1;
}


// Pri returns the primitive root in F2^n
void Field_X::Pri() {
	switch (this->n) {
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

	// ToDo 
	int a = 2, b = 0;                // 
	int* visited = new int[this->m + 1];  // 
	for (int i = 0; i <= this->m; i++) { 
		visited[i] = 0; }

	visited[0], visited[1] = 1, 1;
	srand((int)time(0));

	while (true) {
		//
		int cur = a, i = 1;
		while (cur != 1) {
			visited[cur] = 1;
			//
			cur = this->mul_init(cur, a);
			i++;
		}
		if (i == m) {
			break;
		}

		// 
		b = rand() % (m + 1);
		while (visited[b] == 1) {
			b = rand() % (this->m + 1);
		}
		int j = this->ord_init(b);
		if (j == this->m) {
			a = b;
			break;
		}

		// 
		int g = this->gcd(i, j);
		a = this->mul_init(this->selfMul_init(a, g), b); //a=a^g*b
		if (i * j / this->gcd(i, j) == this->m) {
			break;
		}
	}
	delete visited;
	al = a;
}

Field_X::~Field_X() {
	delete[] irrpb;
	delete[] mg;
	delete[] index_al;
}

// TruthToUn converts the truth table to uni-variate representation
void Field_X::TruthToUn(int* truth, int* un) {
	int order = this->m;
	int* term = this->mg;
	un[order] = 0;
	for (int i = 0; i < order; i++) {
		int t = 0;
		for (int j = 0; j < order; j++) {
			if (truth[term[j]] == 1) {
				int p = (-i * j) % order;
				if (p < 0) {
					p += order;
				}
				t = this->add(t, term[p]);
			}
		}
		un[i] = t;
	}
	int sum = 0;
	for (int i = 0; i < order + 1; i++) {
		sum += truth[i];
	}
	if (sum % 2 != 0) {
		un[0] += 1;
		un[0] %= 2;
		un[order] = 1;
	}
}

// 
bool Field_X::isBoolean(int* un) {
	int order = this->m;
	if (un[0] != 0 && un[0] != 1) { 
		return false; }
	if (un[order] != 0 && un[order] != 1) { 
		return false; }
	for (int i = 1; i < order; i++) {
		int j = (2 * i) % order;
		cout <<i<<":"<<j<<" "<<"un[j],un[i]="<< un[j]<<","<<un[i] << " " << this->mul(un[i], un[i]) << endl;
		cout <<i<<":"<<j<<" "<<"un[j],un[i]="<< un[j]<<","<<un[i] << " " << this->mul_init(un[i], un[i]) << endl;
		if (un[j] != this->mul_init(un[i], un[i])) {	
			return false;
		}
	}
	return true;
}

// UnToTruth calculates the value in x of the boolean function with un as its uni-variate representation.
void Field_X::UnToTruth(int* un, int* truth) {
	int order = this->m;
	truth[0] = un[0];
	for (int x = 1; x < order + 1; x++) {  
		int t = 1;
		for (int j = 0; j <= order; j++) {
			truth[x] = this->add(truth[x], this->mul(t, un[j]));
			t = this->mul(x, t); //x^j
		}
	}
}


int Field_X::tr1(int x) {
	int res = 0;
	int t = x;
	int temp,term;
	for (int i = 0; i < (this->n); i++) {
		temp = this->add(res, t);
		res =temp;
		term = this->mul(t, t);
		t = term;
	}
	return res;
}

void Field_X::Tr(int* un, int* truth) {
	this->UnToTruth(un, truth);
	for (int i = 0; i < this->m + 1; i++) {
		truth[i] = this->tr1(truth[i]);
	}
}

// itob converts int to binary array,
// which is arranged from low level.
void Field_X::itob(int x, int* p, int num) {
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
int Field_X::btoi(int* b, int num) {
	int res = 0, t = 1;
	for (int i = 0; i < num; i++) {
		res += b[i] * t;
		t *= 2;
	}
	return res;
}

void Field_X::div(int* va, int la, int* vb, int lb) {
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
bool Field_X::isDivisible(int a, int b, int num) {
	int* va = new int[num + 1];
	int* vb = new int[num];

	this->itob(a, va, num + 1); 
	this->itob(b, vb, num);
	this->div(va, num + 1, vb, num);
	bool res = (this->btoi(va, num) == 0);
	delete[] va; 
	delete[] vb;

	return res;
}

int Field_X::gcd(int x, int y) {
	int tem;
	while (y != 0) {
		tem = y;
		x = y; 
		y = tem % y;
	}
	return x;
}

int Field_X::get_varnum() {
	return this->n;
}

int Field_X::get_order() {
	return m;
}

int Field_X::get_irrp() {
	return irrp;
}

const int* Field_X::get_irrpb() {
	return irrpb;
}

int Field_X::get_root() {
	return al;
}

const int* Field_X::get_root_list() {
	return mg;
}

const int* Field_X::get_index_al() {
	return index_al;
}




