#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

const int N = 1001;
bool table[N][N];

int main() {
  int V, d;
  while (scanf("%d%d", &V, &d) != EOF) {
    memset(table, false, sizeof(table));

    int prev = 1, curr = 2;
    for (int i = 0; i < V && !table[curr][prev]; ++i) {
      table[curr][prev] = true;
      curr += prev;
      prev = curr - prev;
      curr %= N;
      prev %= N;
    }

    prev = -100000000;
    int ans = 0;
    REP(i, N) {
      REP(j, N) {
        if (table[i][j]) {
          if (i - prev >= d) { ++ans; }
          prev = i;
          break;
        }
      }
    }

    printf("%d\n", ans);
  }
}
