#include <cstdio>
#include <functional>
#include <algorithm>
using namespace std;

int x[100010];
int diff[100010];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
      scanf("%d", x+i);
    }
    if (k >= n) {
      puts("0");
      continue;
    }
    for (int i = 0; i < n-1; ++i) {
      diff[i] = x[i+1] - x[i];
    }
    sort(diff, diff+n-1, greater<int>());
    int sum = 0;
    for (int i = 0; i < k-1; ++i) {
      sum += diff[i];
    }
    printf("%d\n", x[n-1] - x[0] - sum);
  }
}
