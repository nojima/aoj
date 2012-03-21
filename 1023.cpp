#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <climits>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define FOREACH(i, c) for (__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define ALL(c) (c).begin(), (c).end()

inline int sq(int x) { return x*x; }

vector<int> ships[10000];

int main()
{
  int an, bn, r;
  while (scanf("%d%d%d", &an, &bn, &r), an | bn) {
    REP(x, 10000) { ships[x].clear(); }
    REP(i, an) {
      int x, y; scanf("%d%d", &x, &y);
      ships[x].push_back(y);
    }
    REP(x, 10000) { sort(ALL(ships[x])); }
    int ans = 0;
    REP(i, bn) {
      int x, y; scanf("%d%d", &x, &y);
      FOREQ(xx, max(0, x-4*r), min(x+4*r, 9999)) {
        vector<int>::iterator first = lower_bound(ALL(ships[xx]), y-4*r);
        vector<int>::iterator last = upper_bound(ALL(ships[xx]), y+4*r);
        for (vector<int>::iterator it = first; it != last; ++it) {
          int yy = *it;
          if (sq(x - xx) + sq(y - yy) <= sq(4*r)) { ++ans; }
        }
      }
    }
    printf("%d\n", ans);
  }
}
