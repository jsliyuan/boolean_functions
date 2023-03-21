#include "decoder.h"
#include "boolean_fun.h"
using namespace std;

int main() {
	/* 7元2阶 x1x2x3x4 + x1x4x6x7 + x2x3x6x7 + x3x4x5x7
	- 2023.3.17 88s
	- 2023.3.19 8.9s
	- 2023.3.21 2.95s
	*/
	/* 8元3阶 tr(x^254)
	- 2023.3.21 仍内存溢出,初步分析是因为满足条件码字太多，所以加了参数limit_num来限制，但如果要加入limit_num
		这个数该怎么取是个问题。
	*/

	int m = 8;
	int r = 3;
	srand(time(NULL));
	BooleanFun f(m);
	Field gf(m);
	//BooleanFun f(m, "x1x2x3x4+x1x4x6x7+x2x3x6x7+x3x4x5x7");
	f.set_trace_univariate("x^254", gf);
	//f.set_truth_table(0, 1);
	//f.set_truth_table_done();
	//cout << f.get_anf() << endl;
	//for (int i = 0; i < 1 << m; i++) {
	//	f.set_truth_table(i, rand() % 2);
	//}

	int limit_num = 10000000;
	Decoder decoder(r, m, &f,limit_num);
	cout << "test of decoder... " << endl;
	clock_t start, end;
	start = clock();
	int cur_rth_nonlinearty = decoder.r_th_order_nonlinearty();
	cout << "cur_rth_nonlinearty:" << cur_rth_nonlinearty << endl;
	end = clock();
	double t = double(end - start) / CLOCKS_PER_SEC;
	cout << "total time = " << t << endl;
	// 3.17 : 88s  
	return 0;
}