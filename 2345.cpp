#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

void print_float(double x, int precision=15) {
    cout.setf(ios::fixed);
    cout.precision(precision);
    cout << x << '\n';
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int N, M, P;
    while (cin >> N >> M >> P) {
        double p = P/100.0;
        vector<vector<int>> adj(N, vector<int>(N));
        REP(i, M) {
            int u, v; cin >> u >> v; --u; --v;
            ++adj[u][v]; ++adj[v][u];
        }

        vector<int> outedge(1<<N);
        REP(S, 1<<N) {
            int k = 0;
            REP(u, N) if (S & (1<<u))
                REP(v, N) if (~S & (1<<v))
                    k += adj[u][v];
            outedge[S] = k;
        }

        int U = (1<<N)-1;
        vector<double> dp(1<<N);
        REP(S, 1<<N) {
            double q = 0;
            for (int T = (S-1)&S; T; T = (T-1)&S) {
                if ((T&-T) != (S&-S)) continue;
                int k = (outedge[T] + outedge[S^T] - outedge[U^S]) / 2;
                q += dp[T] * pow(p, k);
            }
            dp[S] = 1 - q;
        }
        print_float(dp[U]);
    }
}
