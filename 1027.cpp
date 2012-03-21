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
#define FOREACH(i, c) for (__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)

int main()
{
  int K;
  while (scanf("%d", &K), K) {
    int sum = 0;
    REP(i, K*(K-1)/2) {
      int c; scanf("%d", &c);
      sum += c;
    }
    assert(sum % (K-1) == 0);
    printf("%d\n", sum / (K-1));
  }
}
