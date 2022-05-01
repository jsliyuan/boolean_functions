#include <iostream>
#include <time.h>

#include "boolean_fun.h"

using namespace std;

// data is an array of size n
// Swap two random elements in data for t times
void swap(int *data, int n, int times) {
  for (int i = 0; i < times; i ++) {
    int j = rand() % n;
    int k = rand() % n;
    int tmp = data[j];
    data[j] = data[k];
    data[k] = tmp;
  }
}

int main() {
  BooleanFun f(9);
  int points[(1 << 9)];
  for (int i = 0; i < (1 << 9); i ++) {
    points[i] = i;
  }

  int max_nl = 0;
  while (1) {
    // Initialize f at random
    f.set_truth_table_random();

    // Local search from f
    bool progress = true;
    while (progress) {
      int f_nl = f.nonlinearity();
      swap(points, 1<<9, 50);
      int i = 0;
      progress = false;
      while (i < (1<<9)) {
        int v = f.value_dec(points[i]);
        f.set_truth_table(points[i], v ^ 1);
        int new_nl = f.nonlinearity();
        if (new_nl > max_nl) {
          max_nl = new_nl;
          cout << max_nl << endl;
        }
        if (new_nl > f_nl) {
          progress = true;
          break;
        }
        f.set_truth_table(points[i], v);
        i ++;
      }
    }
  }
  return 0;
}