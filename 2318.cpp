#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int N, E, T;
    while (cin >> N >> E >> T) {
        --T;
        vector<int> start;
        REP(i, N) {
            int w; cin >> w;
            if (w == 1) start.push_back(i);
        }

        // rules[goal][rule][seed]
        vector<vector<vector<int>>> rules(N);
        REP(i, E) {
            int g, c; cin >> g >> c; --g;
            vector<int> seeds(c);
            REP(j, c) {
                cin >> seeds[j];
                --seeds[j];
            }
            rules[g].push_back(move(seeds));
        }

        static const int inf = 1e8;
        vector<int> width(N, inf);
        for (int g : start) width[g] = 1;
        bool updated;
        do {
            updated = false;
            REP(g, N) {
                for (auto& rule : rules[g]) {
                    vector<int> ws(rule.size());
                    REP(i, rule.size())
                        ws[i] = width[rule[i]];
                    sort(ws.begin(), ws.end(), greater<int>());
                    int v = 0;
                    REP(i, ws.size())
                        v = max(v, ws[i]+i);
                    if (v < width[g]) {
                        width[g] = v;
                        updated = true;
                    }
                }
            }
        } while (updated);

        cout << (width[T] < inf ? width[T] : -1) << '\n';
    }
}
