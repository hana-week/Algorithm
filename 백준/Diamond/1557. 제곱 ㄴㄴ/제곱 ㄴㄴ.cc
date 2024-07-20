#include <bits/stdc++.h>
#define i64 long long
#define MAX (i64)1e10
#define SIZE (i64)1'000'010
using namespace std;

int mobius[SIZE] = { 0 };

void _init_mobius() {
  mobius[1] = 1;
  for (int i = 1; i <= SIZE; i++) {
    for (int j = 2 * i; j <= SIZE; j += i) {
      mobius[j] -= mobius[i];
    }
  }
}

i64 compute(i64 n) {
  i64 counts = 0;
  for (i64 i = 1; i * i <= n; i++) {
    counts += mobius[i] * (n / (i * i));
  }
  return counts;
}

int main() {
  _init_mobius();
  i64 k;
  cin >> k;
  i64 l = 0, r = MAX;
  while (l < r - 1) {
    i64 mid = (l + r) / 2;
    if (compute(mid) < k) {
      l = mid;
    } else {
      r = mid;
    }
  }
  cout << r << endl;
  /*
  * in: 1000000000
  * out: (to)
  * 
  i64 i = 0;
  while (1) {
    if (compute(i) == k) {
      cout << i << endl;
      break;
    }
    i++;
  }
  */
}