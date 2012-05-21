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

struct P {
  int x, y;
  P() {}
  P(int x, int y): x(x), y(y) {}
  bool operator==(P& p) const { return x == p.x && y == p.y; }
};

inline bool chain(P p0, P p1) {
  int dx = p1.x-p0.x, dy = p1.y-p0.y;
  return dx == 0 || dy == 0 || dx == dy || dx == -dy;
}

P p[2];
P g;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d%d%d", &p[0].x, &p[0].y, &p[1].x, &p[1].y, &g.x, &g.y);

    if (p[0] == g || p[1] == g) {
      puts("0");
    } else if (chain(p[0], g) && chain(p[1], g)) {
      puts("1");
    } else if (chain(p[0], g) || chain(p[1], g)) {
      puts("2");
    } else if (chain(p[0], p[1])) {
      puts("3");
    } else {
      static const int dy[] = {1, 1, 1, 0};
      static const int dx[] = {0, 1, -1, 1};

      int x0 = p[0].x, y0 = p[0].y, x1 = p[1].x, y1 = p[1].y;
      int ans = 4;
      REP(i, 4) {
        int a0 = dx[i], b0 = dy[i];
        REP(j, 4) if (i != j) {
          int a1 = dx[j], b1 = dy[j];
          int xc = x0*a1*b0 - x1*a0*b1 + (y1-y0)*a0*a1;
          int yc = y1*a1*b0 - y0*a0*b1 - (x1-x0)*b0*b1;
          int d = a1*b0 - a0*b1;
          if (xc%d == 0 && yc%d == 0) {
            if (chain(P(xc/d, yc/d), g)) { ans = 3; }
          }
        }
      }
      printf("%d\n", ans);
    }
  }
}
