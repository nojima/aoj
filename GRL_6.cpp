#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

struct Edge {
    int src, dst, capacity;
    Edge(int src, int dst, int capacity): src(src), dst(dst), capacity(capacity) {}
};
using Graph = vector<vector<Edge>>;

void add_edge(Graph& graph, int src, int dst, int capacity) {
    graph[src].emplace_back(src, dst, capacity);
    graph[dst].emplace_back(dst, src, 0);
}

int augment(const Graph& graph, const vector<int>& level,
            vector<vector<int>>& flow, vector<int>& progress,
            int sink, int u, int f) {
    if (u == sink) return f;
    int total = 0, i = progress[u];
    for (; i < (int)graph[u].size(); ++i) {
        auto& e = graph[u][i];
        int residue = e.capacity - flow[e.src][e.dst];
        if (residue > 0 && level[e.src] < level[e.dst]) {
            int aug = augment(graph, level, flow, progress, sink, e.dst, min(f - total, residue));
            flow[e.src][e.dst] += aug;
            flow[e.dst][e.src] -= aug;
            total += aug;
            if (total == f) break;
        }
    }
    progress[u] = i;
    return total;
}

int dinic(const Graph& graph, int source, int sink) {
    vector<vector<int>> flow(graph.size(), vector<int>(graph.size()));
    int total = 0;
    for (;;) {
        // construct level graph
        vector<int> level(graph.size(), -1); level[source] = 0;
        queue<int> Q; Q.push(source);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            if (level[sink] != -1 && level[u] > level[sink]) break;
            for (auto& e : graph[u]) {
                if (level[e.dst] == -1 && e.capacity - flow[e.src][e.dst] > 0) {
                    level[e.dst] = level[e.src] + 1;
                    Q.push(e.dst);
                }
            }
        }
        if (level[sink] == -1) return total;

        // push blocking flow
        vector<int> progress(graph.size());
        total += augment(graph, level, flow, progress, sink, source, INT_MAX);
    }
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int V, E;
    while (cin >> V >> E) {
        Graph graph(V);
        REP(i, E) {
            int u, v, c; cin >> u >> v >> c;
            add_edge(graph, u, v, c);
        }
        cout << dinic(graph, 0, V-1) << '\n';
    }
}
