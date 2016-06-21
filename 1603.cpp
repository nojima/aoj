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
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define REPEQ(i, n) FOREQ(i, 0, n)
#define ALL(c) (c).begin(), (c).end()

template <typename T> inline int size(const T& x) { return x.size(); }

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int n;
    while (cin >> n, n) {

        vector<int> prices(n);
        REP(i, n) cin >> prices[i];

        static const int MAX_COIN = 100*500;
        vector<pair<int, int>> dp[2];
        REP(i, 2) dp[i].resize(MAX_COIN);

        dp[0][0] = make_pair(0, 0);
        FOR(i, 1, MAX_COIN) dp[0][i] = make_pair(-10000000, 0);

        REP(i, n) {
            int curr = i % 2;
            int next = (i+1) % 2;

            REP(coin, MAX_COIN) {
                dp[next][coin] = make_pair(-10000000, 0);
            }

            REP(coin, MAX_COIN) {
                auto c = dp[curr][coin];
                int change = (1000 - prices[i]%1000) % 1000;

                if (change >= 500) {
                    // 1000円札で買って500円玉が手に入る場合
                    int next_coin = coin + change - 500;
                    if (next_coin < MAX_COIN)
                        dp[next][next_coin] = max(dp[next][next_coin], make_pair(c.first+1, c.second-prices[i]));
                    continue;
                }

                // 買わない場合
                dp[next][coin] = max(dp[next][coin], c);

                if (change + coin >= 500) {
                    // 買う場合で、小銭を払えば500円玉が手に入る場合
                    int next_coin = coin + change - 500;
                    if (next_coin < MAX_COIN)
                        dp[next][next_coin] = max(dp[next][next_coin], make_pair(c.first+1, c.second-prices[i]));
                } else {
                    // 買う場合で、500円玉が入手不可能な場合
                    int next_coin = coin + change;
                    if (next_coin < MAX_COIN)
                        dp[next][next_coin] = max(dp[next][next_coin], make_pair(c.first, c.second-prices[i]));
                }
            }
        }

        auto ans = make_pair(-10000000, 0);
        REP(coin, MAX_COIN) ans = max(ans, dp[n%2][coin]);

        cout << ans.first << ' ' << -ans.second << endl;
    }
}
