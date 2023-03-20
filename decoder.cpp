﻿#include"decoder.h"
#include <cassert>
#include <math.h>

using namespace std;


// 存储f∈RM(r-1,m-i),用string存储
string Decoder::convert_booleanFun_to_string(BooleanFun& f, int len, int* anf_index) {
	string ret;
	//const int* anf = f.get_anf_ptr();
	for (int i = 0; i < len; i++) {
		if (f.get_anf_coe(anf_index[i])) {
			ret.append("1");
		}
		else {
			ret.append("0");
		}
	}
	return ret;
}

// i∈[1,m]; F=F_{i-1},len(F) = 2^(m-i+1)
void Decoder::compute_Li(double eps, int i, int* F, int m, int r, vector<string>& res) {
	//printf("[compute_Li] eps:%f, r:%d, m:%d, i:%d start...\n", eps, r, m, i);
	// 计算V
	//int* V0 = new int[1<<(m - i)];
	//int* V1 = new int[1<<(m - i)];
	for (int j = 0; j < 1 << (m - i); j++) {
		V0[j] = abs(F[j] + F[j + (1 << (m - i))]);
		V1[j] = abs(F[j] - F[j + (1 << (m - i))]);
	}

	// 计算S,记录D
	int* D = new int[1 << (m - i)];
	int S = 0;
	int sumD = 0;
	for (int j = 0; j < 1 << (m - i); j++) {
		D[j] = (V0[j] - V1[j]) / 2;
		sumD += D[j];
		S += (V0[j] + V1[j]) / 2;
	}

	if (m == i || r == 1) {
		if (S - sumD >= pow(2, m) * eps) {
			res.push_back("1");
		}
		if (S + sumD >= pow(2, m) * eps) {
			res.push_back("0");
		}
		return;
	}

	BooleanFun q(m - i);
	double eps_ = pow(2, i) * eps - pow(2, i) * double(S)/pow(2,m);
	//printf("[compute_Li] S:%d, eps:%f\n", S, eps_);
	gamma_r(eps_, 1, &q, D, m - i, r - 1, res);
	//printf("[compute_Li] eps:%f, r:%d, m:%d, i:%d end...\n", eps, r, m, i);

	delete[] D;
}

// int->二进制表示(for test)
string Decoder::int_to_string(int value) {
	string s = "";
	for (; value; value /= 2) {
		if (value % 2) {
			s = '1' + s;
		}
		else {
			s = '0' + s;
		}
	}
	return s;
}

Decoder::Decoder(int r, int m, BooleanFun* f) :r(r), m(m), target_f(f) {
	cout << target_f->get_anf() << endl;;

	// compute anf_index,anf_len
	int len = 1;     // RM(r,m)涉及的所有anf项
	int cur = 1;
	for (int i = 1; i <= r; i++) {
		cur *= (m - i + 1);
		cur /= i;
		len += cur;
	}

	anf_index = new int* [r + 1];
	for (int i = 0; i <= r; i++) {
		anf_index[i] = new int[len];
	}
	anf_len = new int* [r + 1];
	for (int i = 0; i <= r; i++) {
		anf_len[i] = new int[m + 1];
	}

	// init 
	for (int i = 0; i <= m; i++) {
		anf_len[0][i] = 1;
	}
	anf_index[0][0] = 0;

	anf_index[1][0] = 0;
	anf_len[1][0] = 1;
	for (int i = 1; i <= m; i++) {
		anf_index[1][i] = 1 << (i - 1);
		anf_len[1][i] = i + 1;
	}

	// anf_len[i][j]=anf_len[i-1][j]+anf_len[i][j-1]
	// anf_index[i] j增加部分 = anf_index[i-1] j-1之前部分*
	for (int i = 2; i <= r; i++) {
		anf_index[i][0] = 0;
		anf_len[i][0] = 1;
		for (int j = 1; j <= m; j++) {
			anf_len[i][j] = anf_len[i - 1][j - 1] + anf_len[i][j - 1];
			//printf("j:%d; len:%d\n", j, anf_len[i][j]);
			int pre_index = anf_len[i][j - 1];
			for (int k = 0; k < anf_len[i - 1][j - 1]; k++) {
				anf_index[i][pre_index + k] = (1 << (j - 1)) + anf_index[i - 1][k];
				cout << int_to_string(anf_index[i][pre_index + k]);
			}
		}
	}

	// generate F_0
	F_0 = new int[1 << m];
	for (int i = 0; i < 1 << m; i++) {
		F_0[i] = 1 - 2 * target_f->value_dec(i);
	}

	// generate V0,V1,D
	V0 = new int[1<<(m-1)];
	V1 = new int[1<<(m-1)];
}

void Decoder::gamma_r(double eps, int i, BooleanFun* q, int* F, int m, int r, vector<string>& res) {
	//printf("[gamma_r] current m:%d , r: %d ,i:%d, eps: %f start....\n", m, r, i, eps);
	//if (eps > 1) {
	//	//printf("[gamma_r] current m:%d , r: %d ,i:%d, eps: %f end......\n", m, r, i, eps);
	//	return;
	//}
	//if (r == 0 || m == 0) {
	//	int sum = 0;
	//	for (int k = 0; k < 1 << m; k++) {
	//		sum += F[k];
	//	}
	//	if (sum >= pow(2, m) * eps) {
	//		res.emplace_back("0");
	//	}
	//	if (-sum >= pow(2, m) * eps) {
	//		res.emplace_back("1");
	//	}
	//	//printf("[gamma_r] current m:%d , r: %d ,i:%d, eps: %f end......\n", m, r, i, eps);
	//	return;
	//}

	if (this->current_num){
		return;
	}
	
	if (i == m + 1) {
		//if (F[0] < 0) {
		//	q->negate();
		//}
		
		if (abs(F[0]) >= pow(2, m) * eps) {
			if (r==this->r &&m==this->m){
				this->current_num++;
				return ;
			}	
		
			// 转化成string
			string str;
			int index;
			for (int k = 0; k < anf_len[r][m]; k++) {
				index = anf_index[r][k];
				if (q->get_anf_coe(index)) {
					str.append("1");
				}
				else {
					str.append("0");
				}
			}
			if (F[0] >= pow(2, m) * eps) {
				res.push_back(str);
			}
			if (-F[0] >= pow(2, m) * eps) {
				str[0] = '1';
				res.push_back(str);
			}
		}

		//printf("[gamma_r] current m:%d , r: %d ,i:%d, eps: %f end with res ......", m, r, i, eps);
		//cout << str << endl;
		return ;
	}

	BooleanFun q_i(m - i);  // 用来存q_i
	int* F_i = new int[1 << (m - i)];
	vector<string> res_Li;  // 用来储存q_i∈RM(r-1,m-i)

	compute_Li(eps, i, F, m, r, res_Li);
	//printf("[gamma_r] current m:%d , r: %d ,i:%d, eps: %f ,num:%d\n", m, r, i, eps,res_Li.size());
	for (const string& bf : res_Li) {
		// cout << "[gamma_r] bf:" << bf << endl;
		// q^[i] ← q^[i−1] + x_iq_[i]
		for (int k = 0; k < bf.size();k++) {
			int index = anf_index[r - 1][k] + (1 << (m - i));
			if (bf[k] == '1') {
				q_i.set_anf_coe(anf_index[r - 1][k], 1);
				q->set_anf_coe(index, 1);
			}
			else {
				q_i.set_anf_coe(anf_index[r - 1][k], 0);
				q->set_anf_coe(index, 0);
			}
		}

		// compute F_i
		if (r == 1 || m == i) {
			int anf_0 = q_i.get_anf_coe(0);
			for (int k=0;k<1<<(m-i);k++){
				q_i.set_truth_table(k, anf_0);
			}
		}
		else {
			q_i.set_anf_coe_done();
		}

		for (int k = 0; k < (1 << (m - i)); k++) {
			F_i[k] = F[k];
			//printf("%d:q_%d[k]=%d\n", k, i, q_i.value_dec(k));
			if (q_i.value_dec(k)) {
				F_i[k] -= F[k + (1 << (m - i))];
			}
			else {
				F_i[k] += F[k + (1 << (m - i))];
			}
			//cout << F_i[k];
		}
		//cout << endl;

		gamma_r(eps, i + 1, q, F_i, m, r, res);

		// 如果找到了，直接跳出循环	
		if (current_num){
			delete[] F_i;
			return ;
		}

		for (int k = 0; k < (1 << (m - i)); k++) {
			q_i.set_truth_table(k, 0);
		}
		
	}

	// restore q
	for (int k = 0; k < anf_len[r - 1][m - i]; k++) {
		q->set_anf_coe(anf_index[r - 1][k] + (1 << (m - i)), 0);
	}

	delete[] F_i;
	//printf("[gamma_r] current m:%d , r: %d ,i:%d, eps: %f end......\n", m, r, i, eps);
	return ;
}

// 判断ret是否与target_f距离满足<=d
bool Decoder::if_less_than_d(BooleanFun* ret,int d) {
	ret->set_anf_coe_done();
	int sum = 0;
	for (int i = 0; i < 1 << m; i++) {
		if (ret->value_dec(i) != target_f->value_dec(i)) {
			sum++;
		}
	}
	cout << "ret's weight:" << sum << endl;
	return sum <= d;
}

// 半径为d范围有函数则返回true
bool Decoder::main_decoder(int d) {
	double eps = 1 - (double)d / (double)(1 << (m - 1));
	printf("current eps : %f\n", eps);
	BooleanFun q_init(m);

	// restore current_num
	this->current_num=0;

	vector<string> res;
	gamma_r(eps, 1, &q_init, F_0, m, r, res);
	if (res.size()!=0) {
		// 二次校验一下
		//assert(if_less_than_d(ret, d));
		return true;
	}
	else {
		return false;
	}
}

// return the r-th-order nonlinearty of target_f
int Decoder::r_th_order_nonlinearty() {
	int left = 0;
	int right = 1 << (m - 1);
	while (left < right) {
		int mid = (left + right) / 2;
		printf("current interval:[%d, %d]; distance :%d\n", left, right, mid);
		if (main_decoder(mid)) {
			right = mid;
		}
		else {
			left = mid + 1;
		}
	}
	return left;
}