#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

int N, M;
int ans;
unsigned edges[32];

inline int bsf(unsigned x) {
  __asm__("bsf %1, %0;" : "=r"(x) :"r"(x));
  return x;
}

inline int bsr(unsigned x) {
  __asm__("bsr %1, %0;" : "=r"(x) :"r"(x));
  return x;
}

void minimum_dominating_set(unsigned D) {
  if (__builtin_popcount(D) >= ans) { return; }
  bool ok = true;
  for (int x = ~D & ((1<<N)-1); x; x &= x-1) {
    if ((edges[bsf(x)] & D) == 0) { ok = false; break; } 
  }
  if (ok) {
    ans = __builtin_popcount(D);
  } else {
    FOR(i, D ? bsr(D)+1 : 0, N) {
      minimum_dominating_set(D | (1 << i));
    }
  }
}

int main() {
  while (scanf("%d%d", &N, &M), N|M) {
    REP(i, N) { edges[i] = 1 << i; }
    REP(i, M) {
      int s, t; scanf("%d%d", &s, &t);
      edges[s] |= 1 << t;
      edges[t] |= 1 << s;
    }
    ans = 1000;
    minimum_dominating_set(0);
    printf("%d\n", ans);
  }
}
