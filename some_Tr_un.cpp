#include"Galois_field.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

int main(){
  int n=9;
  Field f(n);
  int* truth=new int[f.m+1];
  int* un=new int[f.m+1];
  vector<int> toTest={73};
  ofstream outfile;
  outfile.open("some_un.txt");
  for(int i=0;i<f.m+1;i++){un[i]=truth[i]=0;}
  for (int i=0;i<toTest.size();i++){
    int t=toTest[i];
    un[t]=1;
    outfile<<t<<":\n";
    f.Tr(un,truth);
    printf("Tr %d ok\n",t);
    for (int i=0;i<f.m+1;i++){
      outfile<<truth[i];
    }
    outfile<<endl;
    un[t]=0;
  }
  outfile.close();
  delete truth;delete un;
}