#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i=0;i<int(n);++i)
#define FOR(i, a, b) for(int i=int(a);i<int(b);++i)

int dp[2][256];

template <typename T> inline void assign_min(T& x, T v) { if (v < x) x = v; }
template <typename T> inline T square(T x) { return x*x; }

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int N, M;
    while (cin >> N >> M, N | M) {
        vector<int> codebook(M);
        vector<int> signals(N+1);
        REP(i, M) cin >> codebook[i];
        REP(i, N) cin >> signals[i+1];

        REP(v, 256) dp[0][v] = 1e8;
        dp[0][128] = 0;

        REP(i, N) {
            int curr = i%2;
            int next = (i+1)%2;
            REP(v, 256) dp[next][v] = 1e8;
            REP(v, 256) {
                REP(j, M) {
                    int value = min(max(v + codebook[j], 0), 255);
                    int diff = value - signals[i+1];
                    assign_min(dp[next][value], dp[curr][v] + square(diff));
                }
            }
        }

        cout << *min_element(dp[N%2], dp[N%2]+256) << '\n';
    }
}
