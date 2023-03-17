#include "decoder.h"
#include "boolean_fun.h"
using namespace std;

int main() {
	int m = 8;
	int r = 2;
	srand(time(NULL));
	BooleanFun f(m);
	Field gf(m);
	f.set_trace_univariate("x^7", gf);
	//f.set_truth_table(0, 1);
	//f.set_truth_table_done();
	//cout << f.get_anf() << endl;
	//for (int i = 0; i < 1 << m; i++) {
	//	f.set_truth_table(i, rand() % 2);
	//}
	Decoder decoder(r, m, &f);
	cout << "test of decoder... " << endl;
	clock_t start, end;
	start = clock();
	int cur_rth_nonlinearty = decoder.r_th_order_nonlinearty();
	cout << "cur_rth_nonlinearty:" << cur_rth_nonlinearty << endl;
	end = clock();
	double t = double(end - start) / CLOCKS_PER_SEC;
	cout << "total time = " << t << endl;
	return 0;
}