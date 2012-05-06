#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

const int dy[] = {0, 1, 0, -1};
const int dx[] = {-1, 0, 1, 0};

int y[210], x[210];

int main() {
  int N;
  while (scanf("%d", &N), N) {
    int left = 0, top = 0, right = 1, bottom = 1;
    x[0] = y[0] = 0;
    FOR(i, 1, N) {
      int n, d; scanf("%d%d", &n, &d);
      y[i] = y[n] + dy[d];
      x[i] = x[n] + dx[d];
      left = min(left, x[i]);
      right = max(right, x[i]+1);
      top = min(top, y[i]);
      bottom = max(bottom, y[i]+1);
    }
    printf("%d %d\n", right - left, bottom - top);
  }
}
