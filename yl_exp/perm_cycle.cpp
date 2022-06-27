#include <iostream>
#include <string>
#include <sstream>

#include "../permutation.h"

using namespace std;

// Decompose a permutation in S_9 into cycles.
// Returns the length of each cycle.

// Input: 9,8,4,1,2,7,3,5,6
// Ouput: 6, 3
// Because we can decompose it into two cycles of length 6 and 3.
int main() {
  Permutation p9(9);
  string perm;
  while (1) {
    cin >> perm;
    if (perm == "exit") {
  	  return 0;
    }

    stringstream ss(perm);
    for (int i = 1; i <= 9; i ++) {
      int idx;
      ss >> idx;
      if (ss.peek() == ',') {
      	ss.ignore();
      }
      p9.set(i, idx + 1);
    }
    cout << p9.get_str() << endl;
    for (int len : p9.cycles()) {
      cout << len << " ";
    }
    cout << endl;
  }
  return 0;
}
