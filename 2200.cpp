#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

using Weight = int;
struct Edge {
    int src, dst;
    Weight weight;
};
using Graph = vector<vector<Edge>>;

void add_bidirectional_edge(Graph& graph, int src, int dst, int weight) {
    graph[src].push_back((Edge){src, dst, weight});
    graph[dst].push_back((Edge){dst, src, weight});
}

// Verified: AOJ 2251 (Merry Christmas)
vector<vector<Weight>> warshall_floyd(Graph graph) {
    static const Weight inf = numeric_limits<Weight>::max() / 10;
    vector<vector<Weight>> dist(graph.size(), vector<Weight>(graph.size(), inf));
    REP(u, graph.size()) dist[u][u] = 0;
    REP(u, graph.size()) for (auto& e : graph[u]) dist[e.src][e.dst] = e.weight;
    REP(w, graph.size()) REP(u, graph.size()) REP(v, graph.size())
        dist[u][v] = min(dist[u][v], dist[u][w] + dist[w][v]);
    return dist;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int N, M;
    while (cin>>N>>M, N|M) {
        Graph land(N), sea(N);
        REP(i, M) {
            int x, y, t; char sl;
            cin >> x >> y >> t >> sl;
            --x; --y;
            if (sl == 'L')
                add_bidirectional_edge(land, x, y, t);
            else
                add_bidirectional_edge(sea, x, y, t);
        }
        int R; cin >> R;
        vector<int> order(R);
        REP(i, R) {
            int o; cin >> o;
            order[i] = o-1;
        }

        if (R == 1) {
            cout << "0\n";
            continue;
        }

        auto dist_land = warshall_floyd(land);
        auto dist_sea  = warshall_floyd(sea);

        vector<vector<Weight>> dp(2, vector<Weight>(N, INT_MAX/10));
        dp[1][order[0]] = 0;
        REP(i, R-1) {
            int curr = i%2, prev = 1-i%2;
            int u = order[i], v = order[i+1];
            REP(q, N) {
                Weight value = dp[prev][q] + dist_land[u][v];
                REP(p, N) {
                    value = min(value, dp[prev][p] + dist_land[u][p] + dist_sea[p][q] + dist_land[q][v]);
                }
                dp[curr][q] = value;
            }
        }
        cout << *min_element(dp[(R-2)%2].begin(), dp[(R-2)%2].end()) << '\n';
    }
}
