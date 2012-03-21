#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

const int INF = 100000;
int p[40], t[40];
int memo[5][50];

int opt(int k, int n) {
  if (memo[k][n] != -1) { return memo[k][n]; }
  if (n == 0) {
    if (k == 1 && p[0] <= t[0]) { return memo[k][n] = p[0]; }
  } else {
    if (k == 1) {
      int ret = (n+1)*INF;
      FOREQ(j, 1, 3) {
        if (p[n-1]*(j+1) + p[n] <= t[n]-t[n-1]) {
          ret = min(ret, p[n-1] + p[n] + opt(j, n-1));
        }
      }
      return memo[k][n] = ret;
    } else {
      int dist = abs(p[n]-p[n-1]);
      if (dist*k <= t[n]-t[n-1]) {
        return memo[k][n] = dist + opt(k-1, n-1);
      }
    }
  }
  return memo[k][n] = (n+1)*INF;
}

int main() {
  int n;
  while (scanf("%d", &n), n) {
    memset(memo, -1, sizeof(memo));
    REP(i, n) { scanf("%d%d", p+i, t+i); }
    int ans = INF+INF;
    FOREQ(k, 1, 3) { ans = min(ans, opt(k, n-1)); }
    if (ans < INF) { printf("OK %d\n", ans+p[n-1]); }
    else { printf("NG %d\n", ans/INF); }
  }
}
