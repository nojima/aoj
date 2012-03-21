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

int c[30];
int deps[30];

inline unsigned next_set(unsigned x) {
  unsigned smallest = x & -x;
  unsigned ripple = x + smallest;
  unsigned new_smallest = ripple & -ripple;
  unsigned ones = ((new_smallest / smallest) >> 1) - 1;
  return ripple | ones;
}

inline int bsf(int x) {
  __asm__("bsf %1, %0;" :"=r"(x) :"r"(x));
  return x;
}

int main() {
  int n, U;
  while (scanf("%d%d", &n, &U), n|U) {
    memset(deps, 0, sizeof(deps));
    REP(i, n) {
      int k; scanf("%d%d", &c[i], &k);
      REP(j, k) {
        int r; scanf("%d", &r);
        deps[i] |= 1 << r;
      }
    }
    FOREQ(bits, 1, n) {
      for (int S = (1<<bits)-1; S < (1<<n); S = next_set(S)) {
        int sum = 0;
        bool ok = true;
        for (int T = S; T; T &= T-1) {
          int i = bsf(T);
          sum += c[i];
          if ((S | deps[i]) != S) {
            ok = false;
            break;
          }
        }
        if (sum >= U && ok) {
          printf("%d\n", bits);
          goto next;
        }
      }
    }
next:;
  }
}

