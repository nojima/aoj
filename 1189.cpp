#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

static const int N = 1010;

unordered_map<int, pair<int, int>>
guruguru(vector<vector<int>>& field, const unordered_set<int>& indices)
{
    static int dy[] = { 0, -1, 0, 1 };
    static int dx[] = { 1, 0, -1, 0 };
    int h = field.size();
    int w = field[0].size();
    int y = h / 2;
    int x = w / 2;
    int dir = 0;
    int i = 1;
    int a = 0;          // 最後に曲がってからの歩数
    int b = 1;          // 次に曲がるまでの歩数
    int c = 0;          // 最後に b が増えてからの曲がった回数
    unordered_map<int, pair<int, int>> index2pos;

    while (0 <= y && y < h && 0 <= x && x < w) {
        field[y][x] = i;
        if (indices.find(i) != end(indices))
            index2pos[i] = make_pair(y, x);

        ++i;
        y += dy[dir];
        x += dx[dir];
        ++a;
        if (a == b) {
            dir = (dir + 1) % 4;
            a = 0;
            ++c;
            if (c == 2) {
                ++b;
                c = 0;
            }
        }
    }

    return move(index2pos);
}

vector<bool> sieve(int n)
{
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (prime[i]) {
            for (int j = i * i; j <= n; j += i)
                prime[j] = false;
        }
    }
    return move(prime);
}

int main()
{
    vector<pair<int, int>> inputs;
    unordered_set<int> indices;
    int m, n;
    for (int i = 0; cin >> m >> n, m | n; ++i) {
        inputs.emplace_back(m, n);
        indices.insert(n);
    }

    vector<vector<int>> field(N, vector<int>(N));
    auto index2pos = guruguru(field, indices);
    auto prime = sieve(N * N);

    for (int t = 0; t < (int)inputs.size(); ++t) {
        pair<int, int> ans;
        vector<vector<pair<int, int>>> dp(N, vector<pair<int, int>>(N, make_pair(-10000, 0)));
        int sy = index2pos[inputs[t].second].first;
        int sx = index2pos[inputs[t].second].second;
        ans = dp[sy][sx] = make_pair(prime[field[sy][sx]], (prime[field[sy][sx]] ? field[sy][sx] : 0));
        for (int y = sy + 1; y < N; ++y) {
            for (int x = 1; x < N - 1; ++x) {
                if (field[y][x] > inputs[t].first)
                    continue;
                auto prev = max(dp[y-1][x-1], max(dp[y-1][x], dp[y-1][x+1]));
                if (prime[field[y][x]]) {
                    dp[y][x] = make_pair(prev.first + 1, field[y][x]);
                } else {
                    dp[y][x] = prev;
                }
                ans = max(ans, dp[y][x]);
            }
        }

        cout << ans.first << ' ' << ans.second << endl;
    }
}
