#include "Galois_field.h"
#include "boolean_fun.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <assert.h>

using namespace std;

int main(){
  int n=10;
  Field f(10);
  BooleanFun g(10);
  int al = f.al;
  double minU3 = 1;
  double curU3;
  vector<int> minRes;

  ofstream outfile;
  
  string tt;
  for (int j = 1; j < (1 << n)-1; j++) {
	  cout << "x^i+x^(i+" << j << ")" << endl;
	  for (int i = 0; i < (1 << n); i++) {
		  string str = "x^" + to_string(i) + "+x^" + to_string((i + j) % (1 << n));
		  g.set_trace_univariate(str, &f);
		  //t = g.get_truth_table_ptr();
		  //for (int k = 0; k < 1 << n; k++) {
			 // assert(t[0] == 0 || t[0] == 1);
		  //}
		  curU3 = g.Gowers_norm_u3();
		  if (curU3 < minU3) {
			  minU3 = curU3;
			  tt=g.get_truth_table_hex();
			  minRes.clear();
			  minRes.push_back(1);
		  }
		  else if (curU3 == minU3) {
			  minRes.push_back(i);
		  }
		  printf("%d ,U3=%f\n", i + 1, curU3);
	  }
	  outfile.open("some_un.txt",ios::app);
	  outfile << tt <<endl;
	  outfile << minU3 << endl;
	  outfile.close();

	  minU3=1.00;
  }
  return 0;
}