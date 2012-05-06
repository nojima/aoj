#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

const int INF = 0x0f0f0f0f;

char names[20][30];
int len[20];
int overlap[20][20];
int dp[1<<14][14];

int main() {
  int n;
  while (scanf("%d", &n), n) {
    memset(overlap, 0, sizeof(overlap));
    memset(dp, INF, sizeof(dp));

    REP(i, n) { scanf("%s", names[i]); }

    int k = 0;
    REP(i, n) {
      bool ok = true;
      REP(j, n) {
        if (i == j) { continue; }
        if (strstr(names[j], names[i]) != NULL) {
          ok = false;
          break;
        }
      }
      if (ok) {
        strcpy(names[k], names[i]);
        ++k;
      }
    }

    REP(i, k) { len[i] = strlen(names[i]); }

    REP(i, k) REP(j, k) {
      FOREQ(t, 1, min(len[i], len[j])) {
        if (memcmp(names[i] + len[i] - t, names[j], t) == 0) {
          overlap[i][j] = t;
        }
      }
    }

    REP(now, k) { dp[0][now] = len[now]; }
    FOR(rest, 1, (1<<k)-1) REP(now, k) {
      if (rest & (1 << now)) { continue; }
      REP(next, k) {
        if (~rest & (1 << next)) { continue; }
        dp[rest][now] = min(dp[rest][now],
            dp[rest ^ (1 << next)][next] + len[now] - overlap[now][next]);
      }
    }

    int ans = INF;
    REP(now, k) { ans = min(ans, dp[((1<<k)-1)^(1<<now)][now]); }
    printf("%d\n", ans);
  }
}

