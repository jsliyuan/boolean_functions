#include"decoder.h"
#include <cassert>
#include <math.h>
#include<algorithm>

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
	/*int* V0 = new int[1<<(m - i)];
	int* V1 = new int[1<<(m - i)];*/
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
		//cout << D[j] << " ";
		sumD += D[j];
		S += (V0[j] + V1[j]) / 2;
	}
	/*cout << endl;
	cout << "S:" << S << endl;*/

	if (m == i || r == 1) {
		//int len = anf_len[r - 1][m - i];
		//string str('0', len);
		//if (S - sumD >= pow(2, m) * eps) {
		//	str[0] = '1';
		//	res.push_back(str);
		//}
		//if (S + sumD >= pow(2, m) * eps) {
		//	res.push_back(str);
		//}
		if (S - sumD >= pow(2, m) * eps) {
			res.push_back("1");
		}
		if (S + sumD >= pow(2, m) * eps) {
			res.push_back("0");
		}

		delete[] D;
		return;
	}

	//BooleanFun q(m - i);
	//for (int k = 0; k < 1 << (m - i); k++) {
	//	boolean_funs[i]->set_anf_coe(k, 0);
	//}
	double eps_ = pow(2, i) * eps - pow(2, i) * double(S)/pow(2,m);
	//printf("[compute_Li] eps:%f\n", eps_);
	gamma_r(eps_, 1, boolean_funs[i], D, m - i, r - 1, res);
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

Decoder::Decoder(int r, int m, BooleanFun* f, int limit_num) :r(r), m(m), target_f(f), limit_num(limit_num) {
	cout << target_f->get_anf() << endl;

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
		//cout << i <<"---------------------"<< endl;
		for (int j = 1; j <= m; j++) {
			anf_len[i][j] = anf_len[i - 1][j - 1] + anf_len[i][j - 1];
			//cout << j<<":"<<anf_len[i][j] << endl;
			int pre_index = anf_len[i][j - 1];
			for (int k = 0; k < anf_len[i - 1][j - 1]; k++) {
				anf_index[i][pre_index + k] = (1 << (j - 1)) + anf_index[i - 1][k];
				//cout << anf_index[i][pre_index + k]<<" ";
			}
			//cout << endl;
		}
	}

	// generate F_0
	F_0 = new int[1 << m];
	for (int i = 0; i < 1 << m; i++) {
		F_0[i] = 1 - 2 * target_f->value_dec(i);
		//cout << F_0[i] << " ";
	}
	//cout << endl;

	// init V0,V1
	V0 = new int[1 << (m - 1)];
	V1 = new int[1 << (m - 1)];

	// init boolean_funs
	for (int k = m; k > 0; k--) {
		BooleanFun* f = new BooleanFun(k);
		boolean_funs.push_back(f);
	}

	// init q_i_funs
	for (int k = 0; k < m; k++) {
		BooleanFun* f = new BooleanFun(k);
		q_i_funs.push_back(f);
	}
}

Decoder::~Decoder() {
	for (int i = 0; i <= r; i++) {
		delete[] anf_index[i];
		delete[] anf_len[i];
	}
	delete[] anf_index;
	delete[] anf_len;
	delete[] F_0;
	delete[] V0;
	delete[] V1;
	for (int i = 0; i < m; i++) {
		boolean_funs[i]->~BooleanFun();
		q_i_funs[i]->~BooleanFun();
	}
}

//static bool cmp(const pair<int, string>& a, const pair<int, string>& b) {
//	return a.first > b.first;//根据fisrt的值降序排序
//}

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

	if (this->current_num) {
		return;
	}
	//if (res.size() > limit_num) {
	//	cout << r << " " << m << endl;
	//}

	if (i == m + 1) {
		//if (F[0] < 0) {
		//	q->negate();
		//}
		
		//if (abs(F[0]) >= pow(2, m) * eps) {
			if (this->r == r && this->m == m) {
				this->current_num++;
				if (F[0] < 0) {
					q->negate();
				}
				return;
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
		//}
		return ;
	}

	BooleanFun* q_i = q_i_funs[m - i];  // 用来存q_i
	int* F_i = new int[1 << (m - i)];
	vector<string> res_Li;  // 用来储存q_i∈RM(r-1,m-i)

	compute_Li(eps, i, F, m, r, res_Li);
	//sort(res_Li.begin(), res_Li.end(), cmp);
	//printf("[gamma_r] current m:%d , r: %d ,i:%d, eps: %f ,num:%d\n", m, r, i, eps,res_Li.size());
	//for (const string& bf : res_Li) {
	//	cout << bf << " " ;
	//}
	//cout << endl;
	for (const string& bf : res_Li) {
		// cout << "[gamma_r] bf:" << bf << endl;
		// q^[i] ← q^[i−1] + x_iq_[i]
		for (int k = 0; k < bf.size(); k++) {
			int index = anf_index[r - 1][k] + (1 << (m - i));
			if (bf[k] == '1') {
				q_i->set_anf_coe(anf_index[r - 1][k], 1);
				q->set_anf_coe(index, 1);
			}
			else {
				q_i->set_anf_coe(anf_index[r - 1][k], 0);
				q->set_anf_coe(index, 0);
			}
		}

		// compute F_i
		if (r == 1 || m == i) {
			int anf_0 = q_i->get_anf_coe(0);
			for (int k = 0; k < 1 << (m - i); k++) {
				q_i->set_truth_table(k, anf_0);
			}
		}
		else {
			q_i->set_anf_coe_done();
		}

		for (int k = 0; k < (1 << (m - i)); k++) {
			F_i[k] = F[k];
			//printf("%d:q_%d[k]=%d\n", k, i, q_i.value_dec(k));
			if (q_i->value_dec(k)) {
				F_i[k] -= F[k + (1 << (m - i))];
			}
			else {
				F_i[k] += F[k + (1 << (m - i))];
			}
		}

		gamma_r(eps, i + 1, q, F_i, m, r, res);
		
		if (this->current_num) {
			delete[] F_i;
			vector<string>().swap(res_Li);
			return;
		}		
	}

	// restore q
	for (int k = 0; k < anf_len[r - 1][m - i]; k++) {
		q->set_anf_coe(anf_index[r - 1][k] + (1 << (m - i)), 0);
	}

	// restore q_i
	for (int k = 0; k < 1 << (m - i); k++) {
		q_i->set_anf_coe(k, 0);
	}
	for (int k = 0; k < 1 << (m - i); k++) {
		q_i->set_truth_table(k, 0);
	}

	delete[] F_i;
	//printf("[gamma_r] current m:%d , r: %d ,i:%d, eps: %f end......\n", m, r, i, eps);
	return ;
}

// 判断ret是否与target_f距离满足<=d
int Decoder::if_less_than_d(BooleanFun* ret,int d) {
	ret->set_anf_coe_done();
	int sum = 0;
	for (int i = 0; i < 1 << m; i++) {
		if (ret->value_dec(i) != target_f->value_dec(i)) {
			sum++;
		}
	}
	cout << "ret's weight:" << sum << endl;
	assert(sum <= d);
	return sum;
}

// 半径为d范围有函数则返回true
int Decoder::main_decoder(int d) {
	double eps = 1 - (double)d / (double)(1 << (m - 1));
	printf("current eps : %f\n", eps);
	
	// init boolean_funs[0]
	for (int i = 0; i < 1 << m; i++) {
		boolean_funs[0]->set_anf_coe(i, 0);
	}
	// init q_i_funs
	for (int k = 0; k < m; k++) {
		for (int p = 0; p < 1 << (k); p++) {
			q_i_funs[k]->set_anf_coe(p, 0);
			q_i_funs[k]->set_truth_table(p, 0);
		}
	}

	this->current_num = 0;
	vector<string> res;
	gamma_r(eps, 1, boolean_funs[0], F_0, m, r, res);
	
	if (this->current_num) {
		// 二次校验一下
		return if_less_than_d(boolean_funs[0], d);
	}
	else {
		return -1;
	}
}

// return the r-th-order nonlinearty of target_f
int Decoder::r_th_order_nonlinearty() {
	// 考虑用已有的上下界结论来限制初始区间

	// 下界:概率下界
	int len = 1;     
	int cur = 1;
	for (int i = 1; i <= r; i++) {
		cur *= (m - i + 1);
		cur /= i;
		len += cur;
	}
	int lower_bound = pow(2, m - 1) - pow(2, (double)(m - 1) / 2.0) * sqrt(len);
	//cout << "lower_bound:" << lower_bound << endl;

	// 上界:p(r, n) <= p(r - 1, n - 1) + p(r, n - 1)
	int upper_bound = 1 << (m - 1);
	if (r == 3) {
		if (m == 7) {
			upper_bound = 20;
		}
		else if (m == 8) {
			upper_bound = 60;
		}
		else if (m == 9) {
			upper_bound = 156;
		}
	}
	else if (r == 4) {
		if (m == 7) {
			upper_bound = 8;
		}
		else if (m == 8) {
			upper_bound = 28;
		}
		else if (m == 9) {
			upper_bound = 88;
		}
	}

	int left = max(lower_bound,0);
	int right = min(1 << (m - 1), upper_bound);
	while (left < right) {
		int mid = (left + right) / 2;
		printf("current interval:[%d, %d]; distance :%d\n", left, right, mid);
		int ret = main_decoder(mid);
		if (ret != -1) {
			right = ret;
		}
		else {
			left = mid + 1;
		}
	}
	return left;
}
