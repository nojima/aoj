#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); ++i)

int D[30][30];

int main() {
  int n, m; scanf("%d%d", &n, &m);
  memset(D, 0x0f, sizeof(D));
  REP(i, n) { D[i][i] = 0; }
  REP(i, m) {
    int a, b, c, d; scanf("%d,%d,%d,%d", &a, &b, &c, &d); --a; --b;
    D[a][b] = c; D[b][a] = d;
  }
  int x1, x2, y1, y2; scanf("%d,%d,%d,%d", &x1, &x2, &y1, &y2); --x1; --x2;
  REP(k, n) REP(i, n) REP(j, n) {
    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
  }
  printf("%d\n", y1 - (y2 + D[x1][x2] + D[x2][x1]));
}
