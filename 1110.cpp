#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, n) for (int i = 0; i < n; ++i)

int field[11][5][4];

int dfs(int d) {
  static const int dy[] = {0, 1, 1, 1};
  static const int dx[] = {1, -1, 0, 1};

  if (d == 10) { return 0; }
  int ret = 20 - 2*d;
  REP(y, 5) REP(x, 4) {
    if (field[d][y][x] == -1) { break; }
    REP(k, 4) {
      int ny = y + dy[k], nx = x + dx[k];
      if (nx < 0 || nx >= 4 || ny >= 5) { continue; }
      if (field[d][y][x] == field[d][ny][nx]) {
        int yyy = 0, xxx = 0;
        REP(yy, 5) REP(xx, 4) {
          if (yy == y && xx == x) { continue; }
          if (yy == ny && xx == nx) { continue; }
          field[d+1][yyy][xxx] = field[d][yy][xx];
          ++xxx;
          if (xxx == 4) { ++yyy; xxx = 0; }
        }
        ret = min(ret, dfs(d+1));
      }
    }
  }
  return ret;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    memset(field, -1, sizeof(field));
    REP(y, 5) REP(x, 4) {
      scanf("%d", &field[0][y][x]);
    }
    int ans = dfs(0);
    printf("%d\n", ans);
  }
}
