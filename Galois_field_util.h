#ifndef GALOIS_FIELD_UTIL_H
#define GALOIS_FIELD_UTIL_H

using namespace std;

// itob converts int to binary array,
// which is arranged from low level.
void itob(int x, int* p, int n);

// btoi converts binary array to int.
int btoi(int* b, int n);

void div(int* va, int la, int* vb, int lb);

// IsDivisible decides that whether g can be divided by f in Field F_2.
bool isDivisible(int a, int b, int n);

int gcd(int x, int y);

#endif // !GALOIS_FIELD_UTIL_H