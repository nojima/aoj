#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

template <typename Int>
struct FenwickTree {
  vector<Int> data;
  explicit FenwickTree(int n): data(n, 0) {}
  void add(int i, Int x) { for (; i < (int)data.size(); i |= i+1) data[i] = max(data[i], x); }
  Int sum(int i) const { Int s = 0; for (; i >= 0; i = (i & (i+1)) - 1) s = max(s, data[i]); return s; }
};

long long dp[100001];

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int n;
    while (cin >> n) {
        vector<int> weights(n);
        REP(i, n) cin >> weights[i];

        REP(w, n+1) dp[w] = 0;
        dp[weights[0]] = weights[0];

        FenwickTree<long long> ft(n+1);
        ft.add(weights[0], weights[0]);

        FOR(i, 1, n) {
            int w = weights[i];
            long long v = max(dp[w], ft.sum(w-1) + w);
            dp[w] = v;
            ft.add(w, v);
        }

        long long total_weight = 0;
        REP(i, n) total_weight += weights[i];

        cout << total_weight - ft.sum(n) << '\n';
    }
}
