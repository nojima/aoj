#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

using Weight = int;
struct Edge {
    int src, dst;
    Weight weight;
    Edge(int src, int dst, Weight weight): src(src), dst(dst), weight(weight) {}
};
using Vertex = vector<Edge>;
using Graph = vector<Vertex>;

bool augment(const Graph& graph, vector<bool>& visited, vector<int>& match, int u) {
    if (u == -1) return true;
    for (auto& e : graph[u]) {
        if (!visited[e.dst]) {
            visited[e.dst] = true;
            if (augment(graph, visited, match, match[e.dst])) {
                match[e.src] = e.dst;
                match[e.dst] = e.src;
                return true;
            }
        }
    }
    return false;
}

int bipartie_matching(const Graph& graph, int n_left) {
    vector<int> match(graph.size(), -1);
    int n_match = 0;
    REP(u, n_left) {
        vector<bool> visited(graph.size());
        if (augment(graph, visited, match, u)) ++n_match;
    }
    return n_match;
}

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

    int N, M, L;
    while (cin>>N>>M>>L, N|M|L) {
        Graph graph1(N);
        REP(i, M) {
            int u, v, d; cin >> u >> v >> d;
            graph1[u].emplace_back(u, v, d);
            graph1[v].emplace_back(v, u, d);
        }
        vector<int> positions(L), times(L);
        REP(i, L) cin >> positions[i] >> times[i];

        vector<vector<Weight>> dist = warshall_floyd(graph1);

        Graph graph2(2*L);
        REP(i, L) {
            int t1 = times[i], p1 = positions[i];
            REP(j, L) if (i != j) {
                int t2 = times[j], p2 = positions[j];
                if (dist[p1][p2] <= t2-t1) {
                    graph2[i].emplace_back(i, j+L, 0);
                }
            }
        }
        cout << L - bipartie_matching(graph2, L) << '\n';
    }
}
