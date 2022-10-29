#include"boolean_fun.h"
#include "Galois_field.h"
#include <assert.h>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

int main() {
    // Test truth_table_to_univariate,univariate_to_truth_table
    int n = 10;
    int test_amount = 20;
    Field tf(n);
	BooleanFun g(n);
    for (int k = 0; k < test_amount; k++) {
        g.set_truth_table_random();
        
        string pre = g.get_truth_table_hex();
        g.truth_table_to_univariate(&tf); 
        assert(g.is_univariate_boolean(&tf) == true);
        for (int i = 0; i < (1 << n); i++) {
            g.set_truth_table(i, 0);
        }
        g.univariate_to_truth_table(&tf);
        string cur = g.get_truth_table_hex();
        for (int i = 0; i < (1 << n)/4; i++) {
            //cout<< pre[i]<<" "<< cur[i]<<endl;
            assert(pre[i]==cur[i]);
        }
        //printf("第%d个例子已通过!\n", k + 1);
    }

    // Test set_univariate
    string un_str = "1+x^4+x^8";
    g.set_trace_univariate(un_str,&tf);
    const int* un = g.get_un_ptr();
    assert(un[0] == 1);
    assert(un[4] ==  1);
    assert(un[8] == 1);
    un_str = "0+89x^1+98x^10+999x^987";
    g.set_trace_univariate(un_str,&tf);
    un = g.get_un_ptr();
    assert(un[0] == 0);
    assert(un[1] == 89);
    assert(un[10] == 98);
    assert(un[987] == 999);

    //Performance test of set_trace_univariate
    clock_t start, end;
    start = clock();
    for (int i = 0; i < (1 << n); i++) {
        string str = "x^" + to_string(i)+"+x^"+to_string((2*i)%(1<<n));
        g.set_trace_univariate(str, &tf);
       /* for (int j = 0; j < 1 << n; j++) {
            assert(g.value_dec(j) == 0 || g.value_dec(j) == 1);
        }
        printf("第%d个例子已通过!\n", i+ 1);*/
    }
    end = clock();
    double t = double(end - start) / CLOCKS_PER_SEC;
    cout << "total time = " << t << endl;
    cout << "average time =" <<t/(1<<n) << endl;
}