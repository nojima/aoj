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

bool xy[500][500];
vector<int> xz[500];
vector<int> yz[500];

int main() {
  int n, h;
  while (scanf("%d%d", &n, &h), n|h) {
    memset(xy, false, sizeof(xy));
    REP(i, n) { xz[i].clear(); yz[i].clear(); }
    REP(i, h) {
      char c[3]; int a, b; scanf("%s%d%d", c, &a, &b); --a; --b;
      if (c[1] == 'z') {
        if (c[0] == 'x') { xz[a].push_back(b); }
        else { yz[a].push_back(b); }
      } else {
        xy[b][a] = true;
      }
    }
    REP(i, n) { sort(ALL(xz[i])); sort(ALL(yz[i])); }
    int ans = 0;
    REP(y, n) REP(x, n) {
      if (xy[y][x]) { continue; }
      int cx = xz[x].size(), cy = yz[y].size();
      int i = 0, j = 0, intersection = 0;
      while (i < cx && j < cy) {
        if (xz[x][i] == yz[y][j]) {
          ++intersection; ++i; ++j; }
        else if (xz[x][i] < yz[y][j]) { ++i; }
        else { ++j; }
      }
      ans += n - cx - cy + intersection;
    }
    printf("%d\n", ans);
  }
}

