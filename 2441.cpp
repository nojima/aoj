#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define REPEQ(i, n) FOREQ(i, 0, n)
#define ALL(c) (c).begin(), (c).end()

template <typename T> inline int size(const T& x) { return x.size(); }
typedef long long ll;

ll calc(ll n) {
  ll n_3 = 0, n_5 = 0, n_15 = 0, len = 0;
  for (ll i = 1, j = 10; ; ++i, j *= 10) {
    ll k = min(j - 1, n);
    ll m_3 = k / 3 - n_3, m_5 = k / 5 - n_5, m_15 = k / 15 - n_15;
    len += 4 * (m_3 + m_5);
    len += i * (k - j / 10 + 1 - m_3 - m_5 + m_15);
    n_3 = k / 3; n_5 = k / 5; n_15 = k / 15;
    if (j > n) break;
  }
  return len;
}

int main() {
  cin.tie(0); ios_base::sync_with_stdio(false);

  ll s;
  while (cin >> s) {
    ll lo = 1, hi = 1e18;
    while (lo < hi) {
      ll m = (lo + hi) / 2;
      if (calc(m) < s)
        lo = m + 1;
      else
        hi = m;
    }

    string ans;
    REP(i, 21) {
      ll j = lo + i;
      if (j % 15 == 0)
        ans += "FizzBuzz";
      else if (j % 3 == 0)
        ans += "Fizz";
      else if (j % 5 == 0)
        ans += "Buzz";
      else {
        char str[1024];
        sprintf(str, "%lld", j);
        ans += str;
      }
    }
    ll len = calc(lo - 1);
    cout << ans.substr(s - len - 1, 20) << endl;
  }
}
