#ifndef DECODER_H
#define DECODER_H

#include"boolean_fun.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <queue>

class Decoder {
public:
	int r;			// r�׷����Զ�
	int m;			// mԪ
	BooleanFun* target_f;   // ����Ĳ�������
	int** anf_index;       //  anf_index[i]:��ӦRM(i,j)��anf��
	int** anf_len;	 // 
	int* F_0;
	int current_num;
	int *V0,*V1;

	Decoder(int r, int m, BooleanFun* f);

	// �洢f��RM(r-1,m-i),��string�洢
	std::string convert_booleanFun_to_string(BooleanFun& f, int len, int* anf_index);  


	void compute_Li(double eps, int i, int* F, int m, int r, std::vector<std::string>& res);

	// int->�����Ʊ�ʾ(for test)
	std::string int_to_string(int value);

	void gamma_r(double eps, int i, BooleanFun* q, int* F, int m, int r, std::vector<std::string>& res);

	// �ж�ret�Ƿ���target_f��������<=d
	bool if_less_than_d(BooleanFun* ret,int d);

	bool main_decoder(int d);

	int r_th_order_nonlinearty();
};

#endif