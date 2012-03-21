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

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m), n|m) {
    vector<int> times(n+m);
    REP(i, n) { scanf("%d", &times[i]); }
    REP(i, m) { scanf("%d", &times[i+n]); }
    sort(ALL(times));
    int ans = times[0];
    REP(i, n+m-1) { ans = max(ans, times[i+1] - times[i]); }
    printf("%d\n", ans);
  }
}

