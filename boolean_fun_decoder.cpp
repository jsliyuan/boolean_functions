/*  BooleanFunDecoder is an inheritance of BooleanFun class.
We implement a more fast algorithm to calculate the second-order nonlinearity
of Boolean function in n variables (n<=12), 
denoted by second_order_nonlinearity_Fourquet_Tavernier. 
The algorihtm is in the Fourquet-Tavernier paper.
https://link.springer.com/content/pdf/10.1007/s10623-008-9184-8.pdf.

Moreover, calculating the list of all codewords with degree at most 2 
within (<=) Hamming distance d from the Boolean function can be implemented in
the function, denoted by Fourquet_Tavernier_quadratic_list_decoding(d).
For contrast, we also implement a brute force search method which is super slow
and may only work for n<=5.
*/

#include "boolean_fun.h"
#include "boolean_fun_decoder.h"
#include "reed_muller_generator.h"

#include <memory.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>

using namespace std;

//This is super slow
// only works for n<=5?
std::vector<BooleanFun> BooleanFunDecoder:: quadratic_list_decoding_brute_force(int d){
  ReedMullerGenerator gen(this->var_num(),2);
  vector<BooleanFun> term;
  gen.init();
  BooleanFun f(this->var_num());
  BooleanFun f1(this->var_num());
  f=*gen.get_boolean_fun();
  const int* tt;
  tt=this->get_truth_table_ptr();
  int count=0;
  const int* tt_f;
  tt_f=f.get_truth_table_ptr();
  for(int i=0;i<(1<<this->var_num() );i++){
    f1.set_truth_table(i, ((tt[i] + tt_f[i]) % 2));
    if(((tt[i] + tt_f[i]) % 2) ==1){
      count++;
    }
  }
  if(count<=d){
    term.push_back(f);
  }
  while(gen.next()){
    BooleanFun f(this->var_num());
    BooleanFun f1(this->var_num());
    f=*gen.get_boolean_fun();
    tt_f=f.get_truth_table_ptr();
    int count=0;
    for(int i=0;i<(1<<this->var_num());i++){
      f1.set_truth_table(i, ((tt[i] + tt_f[i]) % 2));
      if(((tt[i] + tt_f[i]) % 2) ==1){
        count++;
      }
    }
    if(count<=d){
      term.push_back(f);
    }
  }
  return term;
}

// Get the initial F_v as input
// The algorihtm is in the Fourquet-Tavernier paper.
int BooleanFunDecoder::initial_Fv(int* &F_v, int m, int v, BooleanFun q_v){
  for(int s=0; s<(1<<(m-v));s++){
    BooleanFun fs(m-v);
    fs=this->restriction(m-v,s);
    BooleanFun f1(m-v);
    f1=fs;
    f1.add(q_v);
    for(int u=0;u<(1<<v);u++){
      int affi_m=u;
      BooleanFun affi(v);
      for(int d=0;d<(1<<v);d++){
        affi.set_anf_coe(d,0);
      }
      for (int c=0; c<v; c++){
        if(affi_m%2==0){
          affi.set_anf_coe(1<<c,0);
        }
        if(affi_m%2==1){
          affi.set_anf_coe(1<<c,1);
        }
        affi_m=affi_m/2;
      }
      affi.set_anf_coe_done();
      affi.add(f1);
      const int* term1;
      term1=affi.get_truth_table_ptr();
      int value1=0;
      for (int j=0; j<(1<<v); j++) {
        if(term1[j]==0){
          value1=value1+1;
        }
        else {
          value1=value1-1;
        }
      }
      F_v[(s<<(v))+u]=value1;
    }
  }
  return 0;
}

// Compute M for all Q_v in [0, 2^(v-1))
// The algorihtm is in the Fourquet-Tavernier paper.
int BooleanFunDecoder::compute_M(int* F_vm1, int v, int m,int s, int Q_v){
  int max_value=0;
  for(int u=0; u<(1<<(v-1)); u++){
    int value;
    int v1=Q_v^u;
    value=abs(F_vm1[(s<<(v-1))+u])+abs(F_vm1[ (s<<(v-1))+ v1 + (1<<(m-1))]);
    if(value>max_value){
      max_value=value;
    }
  }
  return max_value;
}

// For all Q_v in [0, 2^(v-1)), compute
// M[s<<(v-1) + Q_v]
void BooleanFunDecoder::compute_M_fast(int* F_vm1, int v, int m, int s, int* M) {
  // FT algorithm for computing M_s seems wrong.
  // BE CAREFUL!
  // int rem = abs(F_vm1[(s<<(v-1))])%4 + abs(F_vm1[(s<<(v-1)) + (1<<(m-1))])%4;

  // Precompute max_0, max_1
  int max_0 = 0, max_1 = 0;
  for (int u = 0; u < (1 << (v-1)); u ++) {
    //  int x = abs(F_vm1[(s<<(v-1)) + u]) / 4;
    //  int y = abs(F_vm1[(s<<(v-1)) + (1<<(m-1)) + u]) / 4;
    int x = abs(F_vm1[(s<<(v-1)) + u]);
    int y = abs(F_vm1[(s<<(v-1)) + (1<<(m-1)) + u]);
    if (x > max_0) {
      max_0 = x;
    }
    if (y > max_1) {
      max_1 = y;
    }
  }

  vector<int> P0[max_0 + 1];
  vector<int> P1[max_1 + 1];
  for (int u = 0; u < (1 << (v-1)); u ++) {
    // int x = abs(F_vm1[(s<<(v-1)) + u]) / 4;
    // int y = abs(F_vm1[(s<<(v-1)) + (1<<(m-1)) + u]) / 4;
    int x = abs(F_vm1[(s<<(v-1)) + u]);
    int y = abs(F_vm1[(s<<(v-1)) + (1<<(m-1)) + u]);
    // Put u in P0[x] and P1[y]
    P0[x].push_back(u);
    P1[y].push_back(u);
  }

  // Initialize M_s to -1
  for (int Q = 0; Q < (1 << (v-1)); Q ++) {
    M[(s<<(v-1)) + Q] = -1;
  }

  // Determine M_s[Q_v] for all Q_v
  int determined_count = 0;
  int z = max_0 + max_1;
  while (determined_count < (1 << (v-1))) {
    for (int x = 0; x <= max_0; x ++) {
      if (x > z) {
        break;
      }
      int y = z - x;
      if (y > max_1) {
        continue;
      }
      for (int x_u : P0[x]) {
        for (int y_v : P1[y]) {
          int Q = x_u ^ y_v;
          if (M[(s<<(v-1)) + Q] == -1) {
            // The original FT algorithm -- see comments above.
            // M[(s<<(v-1)) + Q] = z*4 + rem;
            M[(s<<(v-1)) + Q] = z;
            determined_count ++;
          }
        }
      }
    }
    z --;
  }
}

// Compute F_v from F_vm1 for all Q_v in [0, 2^(v-1))
int BooleanFunDecoder::compute_Fv(int* &F_v, int* F_vm1, int Q_v,int m,int v){
  for (int s=0; s<(1<<(m-v));s++){
    for(int u=0; u<(1<<(v));u++){
      int u_v=u%2;
      int u_vm1=(u>>1);
      F_v[(s<<v)+u]= F_vm1[(s<<(v-1))+u_vm1]+ pow(-1,u_v)*F_vm1[(s<<(v-1)) + (1<<(m-1)) +(Q_v ^ u_vm1)];
    }
  }
  return 0;
}

// For list decoding algoritm
// The algorihtm is in the Fourquet-Tavernier paper.
void BooleanFunDecoder::sums(std::vector<BooleanFun>& store,double eps, int v,int m, BooleanFun q_vm1, int* F_vm1){
  int M[(1<<(m-1))];
 
  // Step 1. compute M from F_vm1
  for (int s=0; s<(1<<(m-v));s++){
    // Slow approach
    // TODO: cleanup when stable
    
    for(int Q_v=0; Q_v<(1<<(v-1)); Q_v++){
      M[(s<<(v-1))+Q_v]=compute_M(F_vm1,v,m,s,Q_v);
    }
    
    //compute_M_fast(F_vm1, v, m, s, M);
  }
  
  // Step 2. Compute Gamma_v from M
  int Gamma_v[(1<<(v-1))];
  for (int c=0;c<(1<<(v-1));c++){
    Gamma_v[c]=0;
  }
  for(int Q_v=0; Q_v< (1<<(v-1)); Q_v++){
    for(int s=0; s< (1<<(m-v)); s++){
      Gamma_v[Q_v] = Gamma_v[Q_v] + M[Q_v+(s<<(v-1))];
    }   
  }

  // Step 3. Compute L_v from Q_v whose "distance" is >= 2n*eps
  vector<int> L_v;
  for(int Q_v=0; Q_v<(1<<(v-1)); Q_v++ ){
    if(Gamma_v[Q_v] >= ((1<<(m+1))*eps)){
      L_v.push_back(Q_v);
    }  
  }

  // Step 4. For each "good" Q_v, recursion
  for(vector<int>::iterator it= L_v.begin();it!=L_v.end();it++){
    // Step 4.1 compute F_v from F_vm1 and Q_v
    int* F_v;
    F_v = new int[(1<<m)];
    
    compute_Fv(F_v, F_vm1, *it,m,v);
    
    if (v < m){
      BooleanFun Qv(v-1);
      int Qv_1=(*it);
      for(int j=0;j<(1<<(v-1));j++){
        Qv.set_anf_coe(j,0);
      }
      for (int j=0 ; j<v-1; j++){
        if(Qv_1%2==0){
          Qv.set_anf_coe(1<<j,0);
        }
        if(Qv_1%2==1){
          Qv.set_anf_coe(1<<j,1);
        }
        Qv_1=Qv_1/2;
      }
      
      Qv.set_anf_coe_done();
      const int* tt;
      tt=Qv.get_truth_table_ptr();
      const int* tt1;
      tt1=q_vm1.get_truth_table_ptr();
      BooleanFun q(v);
      BooleanFun q_trans(v);
      int count=0;
      for(int t=0;t<(1<<(v));) {
        q.set_truth_table(t,0);
        q.set_truth_table(t+1,tt[count]);
        count++;
        t=t+2;
      }
      q.set_truth_table_done();
      count=0;
      for(int p=0;p<(1<<(v));) {
        q_trans.set_truth_table(p,tt1[count]);
        q_trans.set_truth_table(p+1,tt1[count]);
        count++;
        p=p+2;
      }
      q_trans.set_truth_table_done();
      q.add(q_trans);
      sums(store,eps, v+1,m, q, F_v);
    }
      
    else {
      int Qv_bin;
      Qv_bin=*it;
      BooleanFun Qv(v-1);
      for(int j=0;j<(1<<(v-1));j++){
        Qv.set_anf_coe(j,0);
      }
      for (int j=0; j<v-1; j++){
        if(Qv_bin%2==0){
          Qv.set_anf_coe(1<<j,0);
        }
        if(Qv_bin%2==1){
          Qv.set_anf_coe(1<<j,1);
        }
        Qv_bin=Qv_bin/2;
      }
      Qv.set_anf_coe_done();
      const int* tt;
      tt=Qv.get_truth_table_ptr();
      const int* tt1;
      tt1=q_vm1.get_truth_table_ptr();
      BooleanFun q(m);
      BooleanFun q_trans(m);
      int count=0;
      for(int t=0;t<(1<<(m));) {
        q.set_truth_table(t,0);
        q.set_truth_table(t+1,tt[count]);
        count++;
        t=t+2;
      }
      q.set_truth_table_done();
      count=0;
      for(int p=0;p<(1<<(m));) {
        q_trans.set_truth_table(p,tt1[count]);
        q_trans.set_truth_table(p+1,tt1[count]);
        count++;
        p=p+2;
      }
      q_trans.set_truth_table_done();
      q.add(q_trans);
      
      for(int j=0;j<(1<<m);j++){
        int affi_m=j;
        if(abs(F_v[j])>=(double)(1<<(m+1))*eps){
          BooleanFun q_term(q);
          BooleanFun affi(m);
          for(int d=0;d<(1<<m);d++){
            affi.set_anf_coe(d,0);
          }
          for (int c=0; c<m; c++){
            if(affi_m%2==0){
              affi.set_anf_coe(1<<c,0);
            }
            if(affi_m%2==1){
              affi.set_anf_coe(1<<c,1);
            }
            affi_m=affi_m/2;
          }
          if(F_v[j]<0){
            affi.set_anf_coe(0,1);
          }
          affi.set_anf_coe_done();
          q_term.add(affi);
          store.push_back(q_term);
          //cout<<"the result is "<<q_term.get_anf()<<endl;
        }
      }
    // clean up
    }
    delete F_v;
  }
}

// For list decoding algoritm
// The algorihtm is in the Fourquet-Tavernier paper.
int BooleanFunDecoder::sums1(bool &flag,double eps, int v,int m, BooleanFun q_vm1, int* F_vm1){
  int M[(1<<(m-1))];
 
  // Step 1. compute M from F_vm1
  for (int s=0; s<(1<<(m-v));s++){
    for(int Q_v=0; Q_v<(1<<(v-1)); Q_v++){
      M[(s<<(v-1))+Q_v]=compute_M(F_vm1,v,m,s,Q_v);
    }
    
    //compute_M_fast(F_vm1, v, m, s, M);
  }
  
  // Step 2. Compute Gamma_v from M
  int Gamma_v[(1<<(v-1))];
  for (int c=0;c<(1<<(v-1));c++){
    Gamma_v[c]=0;
  }
  for(int Q_v=0; Q_v< (1<<(v-1)); Q_v++){
    for(int s=0; s< (1<<(m-v)); s++){
      Gamma_v[Q_v] = Gamma_v[Q_v] + M[Q_v+(s<<(v-1))];
    }   
  }

  // Step 3. Compute L_v from Q_v whose “distance” is >= 2n*eps
  vector<int> L_v;
  for(int Q_v=0; Q_v<(1<<(v-1)); Q_v++ ){
    if(Gamma_v[Q_v] >= ((1<<(m+1))*eps)){
      L_v.push_back(Q_v);
    }  
  }

  // Step 4. For each "good" Q_v, recursion
  for(vector<int>::iterator it= L_v.begin();it!=L_v.end();it++){
    // Step 4.1 compute F_v from F_vm1 and Q_v
    int* F_v;
    F_v = new int[(1<<m)];
    
    compute_Fv(F_v, F_vm1, *it,m,v);
    
    if (v < m){
      BooleanFun Qv(v-1);
      int Qv_1=(*it);
      for(int j=0;j<(1<<(v-1));j++){
        Qv.set_anf_coe(j,0);
      }
      for (int j=0 ; j<v-1; j++){
        if(Qv_1%2==0){
          Qv.set_anf_coe(1<<j,0);
        }
        if(Qv_1%2==1){
          Qv.set_anf_coe(1<<j,1);
        }
        Qv_1=Qv_1/2;
      }
      
      Qv.set_anf_coe_done();
      const int* tt;
      tt=Qv.get_truth_table_ptr();
      const int* tt1;
      tt1=q_vm1.get_truth_table_ptr();
      BooleanFun q(v);
      BooleanFun q_trans(v);
      int count=0;
      for(int t=0;t<(1<<(v));) {
        q.set_truth_table(t,0);
        q.set_truth_table(t+1,tt[count]);
        count++;
        t=t+2;
      }
      q.set_truth_table_done();
      count=0;
      for(int p=0;p<(1<<(v));) {
        q_trans.set_truth_table(p,tt1[count]);
        q_trans.set_truth_table(p+1,tt1[count]);
        count++;
        p=p+2;
      }
      q_trans.set_truth_table_done();
      q.add(q_trans);
      if(flag==false){
        sums1(flag,eps, v+1,m, q, F_v);
      }
      else{
        delete F_v;
        return 0;
      }
    }
      
    else {
      int Qv_bin;
      Qv_bin=*it;
      BooleanFun Qv(v-1);
      for(int j=0;j<(1<<(v-1));j++){
        Qv.set_anf_coe(j,0);
      }
      for (int j=0; j<v-1; j++){
        if(Qv_bin%2==0){
          Qv.set_anf_coe(1<<j,0);
        }
        if(Qv_bin%2==1){
          Qv.set_anf_coe(1<<j,1);
        }
        Qv_bin=Qv_bin/2;
      }
      Qv.set_anf_coe_done();
      const int* tt;
      tt=Qv.get_truth_table_ptr();
      const int* tt1;
      tt1=q_vm1.get_truth_table_ptr();
      BooleanFun q(m);
      BooleanFun q_trans(m);
      int count=0;
      for(int t=0;t<(1<<(m));) {
        q.set_truth_table(t,0);
        q.set_truth_table(t+1,tt[count]);
        count++;
        t=t+2;
      }
      q.set_truth_table_done();
      count=0;
      for(int p=0;p<(1<<(m));) {
        q_trans.set_truth_table(p,tt1[count]);
        q_trans.set_truth_table(p+1,tt1[count]);
        count++;
        p=p+2;
      }
      q_trans.set_truth_table_done();
      q.add(q_trans);
      
      for(int j=0;j<(1<<m);j++){
        int affi_m=j;
        if(abs(F_v[j])>=(double)(1<<(m+1))*eps){
          flag=true;
          break;
        }
      }
      if(flag){
        delete F_v;
        return 0;
      }
    // clean up
    }
    delete F_v;
  }
  return 0;
}

// Returns all codewords with degree at most 2 within (<=) Hamming distance d
std::vector<BooleanFun> BooleanFunDecoder::Fourquet_Tavernier_quadratic_list_decoding(int d){
  std::vector<BooleanFun> store;
  double eps=0.5-(double)((double)d/(double)(1<<(this->var_num())));
  //cout<<"eps is "<<eps<<endl;
  BooleanFun q_v_1(1,"0");
  int* initial_arry;
  initial_arry = new int[(1<<(this->var_num()))];
  initial_Fv(initial_arry, this->var_num(), 1, q_v_1);
  
  sums(store,eps,2,this->var_num(),q_v_1,initial_arry);
  return store;
}

// Returns all codewords with degree at most 2 within (<=) Hamming distance d
int BooleanFunDecoder::list_decoding_quit(int d){
  double eps=0.5-(double)((double)d/(double)(1<<(this->var_num())));
  //cout<<"eps is "<<eps<<endl;
  BooleanFunDecoder q_v_1(1,"0");
  int* initial_arry;
  initial_arry = new int[(1<<(this->var_num()))];
  initial_Fv(initial_arry, this->var_num(), 1, q_v_1);
  bool flag=false;
  sums1(flag,eps,2,this->var_num(),q_v_1,initial_arry);
  if(flag==true)
    return 1;
  else
    return 0;
}

// Compute the second order nonlinearity using Fourquet-Tavernier list decoding algorithm.
int BooleanFunDecoder::second_order_nonlinearity_Fourquet_Tavernier(){
  int min,max,middle;
  min=0;
  max=(1<<(this->var_num()))-2;
  middle=(min+max)/2;
  while(min<=max){
    if(this->list_decoding_quit(middle)==1){
      max=middle-1;
      middle=(min+max)/2;
    } 
    else{
      min=middle+1;
      middle=(min+max)/2;
    }
  }
  return min;
}



