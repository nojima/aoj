#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

struct FenwickTree {
  vector<ll> data;
  explicit FenwickTree(int n): data(n, 0) {}
  void add(int i, ll x) { for (; i < (int)data.size(); i |= i + 1) data[i] += x; }
  ll sum(int i) const { ll s = 0; for (; i >= 0; i = (i & i + 1) - 1) s += data[i]; return s; }
};

struct Bug { ll emission, acceptable; int index; };

int main() {
  int N;
  while (cin >> N) {
    vector<Bug> bugs(N);
    for (int i = 0; i < N; ++i)
      cin >> bugs[i].emission >> bugs[i].acceptable;

    FenwickTree ft1(N), ft2(N);
    sort(begin(bugs), end(bugs), [](const Bug& a, const Bug& b) { return a.emission < b.emission; });
    for (int i = 0; i < N; ++i) {
      bugs[i].index = i;
      ft1.add(i, bugs[i].emission);
      ft2.add(i, 1);
    }

    ll answer = 0;
    sort(begin(bugs), end(bugs), [](const Bug& a, const Bug& b) { return a.acceptable < b.acceptable; });
    for (const Bug& b : bugs) {
      int lo = 0, hi = N;
      while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (ft1.sum(mid) <= ft2.sum(mid) * b.acceptable)
          lo = mid + 1;
        else
          hi = mid;
      }
      if (lo > 0) answer = max(answer, ft2.sum(lo - 1));
      ft1.add(b.index, -b.emission);
      ft2.add(b.index, -1);
    }
    cout << answer << endl;
  }
}
