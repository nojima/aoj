#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
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

const int INF = 1000000000;
int value[] = {500, 100, 50, 10, 5, 1};

int opt(int p, int num[])
{
  int ret = 0;
  REP(i, 6) {
    int use = min(num[i], p / value[i]);
    p -= value[i] * use;
    ret += use;
  }
  return p ? INF : ret;
}

int main()
{
  int p;
  while (scanf("%d", &p), p) {
    int num[6], sum = 0;
    REP(i, 6) {
      scanf("%d", &num[5-i]);
      sum += num[5-i] * value[5-i];
    }
    int big[] = {INF, INF, INF, INF, INF, INF};
    int ans = INF;
    FOREQ(i, p, min(sum, p + 10000)) {
      ans = min(ans, opt(i, num) + opt(i - p, big));
    }
    printf("%d\n", ans);
  }
}
