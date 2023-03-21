#ifndef DECODER_H
#define DECODER_H

#include"boolean_fun.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <queue>

class Decoder {
public:
	int r;			// r阶非线性度
	int m;			// m元
	BooleanFun* target_f;   // 解码的布尔函数
	int** anf_index;       //  anf_index[i]:对应RM(i,j)的anf项
	int** anf_len;	 // 
	int* F_0;
	int* V0, * V1;
	int current_num;
	std::vector<BooleanFun*> boolean_funs;  // 用于gamma_r中参数传递
	std::vector<BooleanFun*> q_i_funs;      // 用于记录q_i
	int limit_num;  // 用来限制每次gamma_r调用的返回函数数量

	Decoder(int r, int m, BooleanFun* f, int limit_num);

	~Decoder();

	// 存储f∈RM(r-1,m-i),用string存储
	std::string convert_booleanFun_to_string(BooleanFun& f, int len, int* anf_index);  


	void compute_Li(double eps, int i, int* F, int m, int r, std::vector<std::string>& res);

	// int->二进制表示(for test)
	std::string int_to_string(int value);

	void gamma_r(double eps, int i, BooleanFun* q, int* F, int m, int r, std::vector<std::string>& res);

	// 判断ret是否与target_f距离满足<=d
	bool if_less_than_d(BooleanFun* ret,int d);

	bool main_decoder(int d);

	int r_th_order_nonlinearty();
};

#endif