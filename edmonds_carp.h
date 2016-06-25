struct Edge {
    int src, dst, capacity;
    Edge(int src, int dst, int capacity): src(src), dst(dst), capacity(capacity) {}
};
using Graph = vector<vector<Edge>>;

void add_edge(Graph& graph, int src, int dst, int capacity) {
    graph[src].emplace_back(src, dst, capacity);
    graph[dst].emplace_back(dst, src, 0);
}

// Verified: AOJ 1163 (Cards)
int edmonds_karp(const Graph& graph, int source, int sink) {
    vector<vector<int>> flow(graph.size(), vector<int>(graph.size()));
    Edge dummy(-1, -1, -1);
    int total = 0;
    for (;;) {
        // find path
        queue<int> Q; Q.push(source);
        vector<const Edge*> prev(graph.size()); prev[source] = &dummy;
        while (!Q.empty() && prev[sink] == nullptr) {
            int u = Q.front(); Q.pop();
            for (auto& e : graph[u]) {
                if (prev[e.dst] == nullptr && e.capacity - flow[e.src][e.dst] > 0) {
                    prev[e.dst] = &e;
                    Q.push(e.dst);
                }
            }
        }
        if (prev[sink] == nullptr) return total;

        // augment flow
        int f = INT_MAX;
        for (int u = sink; prev[u] != &dummy; u = prev[u]->src) {
            auto e = prev[u];
            f = min(f, e->capacity - flow[e->src][e->dst]);
        }
        for (int u = sink; prev[u] != &dummy; u = prev[u]->src) {
            auto e = prev[u];
            flow[e->src][e->dst] += f;
            flow[e->dst][e->src] -= f;
        }
        total += f;
    }
}

