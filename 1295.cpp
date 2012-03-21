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

int main() {
  int w, d;
  while (scanf("%d%d", &w, &d), w|d) {
    int h, ans = 0;
    int hist1[21] = {}, hist2[21] = {};
    REP(i, w) { scanf("%d", &h); hist1[h]++; ans += h; }
    REP(i, d) { scanf("%d", &h); hist2[h]++; ans += h; }
    REP(h, 21) { ans -= h * min(hist1[h], hist2[h]); }
    printf("%d\n", ans);
  }
}
