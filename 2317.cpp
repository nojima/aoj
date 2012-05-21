#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
typedef long long ll;

ll s[100010], t[100010], p[100010];
ll counts[2][100010];

int main() {
  ll N, M; scanf("%lld%lld", &N, &M);
  REP(i, N) { scanf("%lld%lld", s+i, t+i); }
  REP(i, M) { scanf("%lld", p+i); }
  sort(p, p+M);

  ll ret = 0;
  REP(i, N) {
    int s_index = lower_bound(p, p+M, s[i]) - p;
    int t_index = lower_bound(p, p+M, t[i]) - p;
    if (s_index == t_index) {
      ret += abs(t[i] - s[i]);
    } else {
      int group = s_index % 2;
      if (s_index < t_index) { --t_index; }
      else { --s_index; }
      ret += abs(s[i] - p[s_index]);
      if ((s_index + t_index) % 2) { ret += abs(t[i] - p[t_index]); }
      counts[group][min(s_index, t_index) + 1] += 1;
      counts[group][max(s_index, t_index) + 1] -= 1;
    }
  }

  REP(group, 2) {
    ll sum = 0;
    FOR(i, 1, M) {
      sum += counts[group][i];
      if (i % 2 == group) { ret += sum * (p[i] - p[i-1]); }
    }
  }

  printf("%lld\n", ret);
}
