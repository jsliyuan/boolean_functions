using namespace std;

// itob converts int to binary array,
// which is arranged from low level.
void itob(int x, int* p, int n) {
	for (int i = 0; i < n; i++) {
		if (x > 0) {
			p[i] = x % 2;
			x /= 2;
		}
		else {
			p[i] = 0;
		}
	}
}

// btoi converts binary array to int.
int btoi(int* b, int n) {
	int res = 0, t = 1;
	for (int i = 0; i < n; i++) {
		res += b[i] * t;
		t *= 2;
	}
	return res;
}

// 计算va除以vb的余数
// va,vb是低位开始
// 结果记录在va上
void div(int* va, int la, int* vb, int lb) {
	int pa, pb;  //记录va，vb第一个不为0的位置
	for (pa = la - 1; pa >= 0; pa--) {
		if (va[pa] != 0) { break; }
	}
	for (pb = lb - 1; pb >= 0; pb--) {
		if (vb[pb] != 0) { break; }
	}
	while (pa >= pb) {
		//printf("current pa:%d,pb:%d\n",pa,pb);
		int p = -1;  //记录下一个不等于0的位置
		for (int i = 0; i <= pb; i++) {
			va[pa - i] ^= vb[pb - i];
			if (va[pa - i] == 1 && p == -1) {
				p = pa - i;
			}
		}
		pa = p != -1 ? p : pa - pb - 1;
	}
}

// IsDivisible decides that whether g can be divided by f in Field F_2.
bool isDivisible(int a, int b, int n) {
	int* va = new int[n + 1];
	int* vb = new int[n];
	itob(a, va, n + 1); itob(b, vb, n);
	div(va, n + 1, vb, n);
	bool res = (btoi(va, n) == 0);
	delete[] va; delete[] vb;
	return res;
}

int gcd(int x, int y) {
	int tem;
	while (y != 0) {
		tem = y;
		x = y; y = tem % y;
	}
	return x;
}