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

char field[30][30];

int dfs(int y, int x) {
  static int dy[] = {-1, 0, 1, 0};
  static int dx[] = {0, -1, 0, 1};

  if (field[y][x] == '.') {
    field[y][x] = '#';
    int sum = 1;
    REP(k, 4) { sum += dfs(y + dy[k], x + dx[k]); }
    return sum;
  } else {
    return 0;
  }
}

int main() {
  int W, H;
  while (scanf("%d%d", &W, &H), W|H) {
    int sy = -1, sx = -1;
    memset(field, '#', sizeof(field));
    FOREQ(y, 1, H) FOREQ(x, 1, W) {
      scanf(" %c", &field[y][x]);
      if (field[y][x] == '@') {
        sy = y; sx = x;
        field[y][x] = '.';
      }
    }
    printf("%d\n", dfs(sy, sx));
  }
}

