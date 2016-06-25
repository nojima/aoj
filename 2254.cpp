#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i=0;i<int(n);++i)
#define FOR(i, a, b) for(int i=int(a);i<int(b);++i)

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int N;
    while (cin >> N, N) {
        vector<vector<int>> costs(N, vector<int>(N+1));
        REP(i, N) REP(j, N+1) cin >> costs[i][j];

        vector<int> dp(1<<N);
        dp[0] = 0;
        FOR(S, 1, 1<<N) {
            int v = INT_MAX;
            REP(i, N) if (S & (1<<i)) {
                int c = costs[i][0];
                REP(j, N) if (~S & (1<<j)) {
                    c = min(c, costs[i][j+1]);
                }
                v = min(v, dp[S^(1<<i)] + c);
            }
            dp[S] = v;
        }
        cout << dp[(1<<N)-1] << '\n';
    }
}
