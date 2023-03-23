#include "decoder.h"
#include "boolean_fun.h"
using namespace std;

int main() {
	/* 7Ԫ2�� x1x2x3x4 + x1x4x6x7 + x2x3x6x7 + x3x4x5x7
	- 2023.3.17 88s
	- 2023.3.19 8.9s
	- 2023.3.21 2.95s
	*/
	/* 8Ԫ3�� tr(x^254)
	- 2023.3.21 ���ڴ����,������������Ϊ������������̫�࣬���Լ��˲���limit_num�����ƣ������Ҫ����limit_num
		���������ôȡ�Ǹ����⡣
	- 2023.3.22 �������Ͻ�60�����ƣ�����100s�ܳ��������ǽ����50�������ĸ�����48�����������
	- 2023.3.24 ��ȷ�ˣ����� ��ʱ:62s
	*/

	int m = 8;
	int r = 3;
	srand(time(NULL));
	Field gf(m);
	BooleanFun f(m);
	f.set_trace_univariate("x^254", gf);
	//BooleanFun f(m, "x1x2x3x4+x1x4x6x7+x2x3x6x7+x3x4x5x7");
	//BooleanFun f(m, "x1x2x4x5 + x1x2x3x6 + x1x3x4x7 + x2x3x5x7+ x2x4x5x7 + x2x4x6x7");
	//f.set_truth_table(0, 1);
	//f.set_truth_table_done();
	//cout << f.get_anf() << endl;
	//for (int i = 0; i < 1 << m; i++) {
	//	f.set_truth_table(i, rand() % 2);
	//}

	int limit_num = 100000000;
	Decoder decoder(r, m, &f,limit_num);
	cout << "test of decoder... " << endl;
	clock_t start, end;
	start = clock();
	//decoder.main_decoder(1);
	int cur_rth_nonlinearty = decoder.r_th_order_nonlinearty();
	cout << "cur_rth_nonlinearty:" << cur_rth_nonlinearty << endl;
	end = clock();
	double t = double(end - start) / CLOCKS_PER_SEC;
	cout << "total time = " << t << endl;
	// 3.17 : 88s  
	return 0;
}