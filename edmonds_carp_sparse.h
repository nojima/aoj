struct Edge {
    int src, dst;
    int capacity, flow;
    Edge* rev;
    Edge(int src, int dst, int capacity): src(src), dst(dst), capacity(capacity), flow(0), rev(nullptr) {}
};
using Graph = vector<vector<Edge>>;

void add_edge(Graph& graph, int src, int dst, int capacity) {
    graph[src].emplace_back(src, dst, capacity);
    graph[dst].emplace_back(dst, src, 0);
    graph[src].back().rev = &graph[dst].back();
    graph[dst].back().rev = &graph[src].back();
}

inline int residue(const Edge& edge) { return edge.capacity - edge.flow; }

// Verified: AOJ 1163 (Cards)
int edmonds_karp(Graph& graph, int source, int sink) {
    Edge dummy(-1, -1, -1);
    int total = 0;
    for (;;) {
        // find path
        queue<int> Q; Q.push(source);
        vector<Edge*> prev(graph.size()); prev[source] = &dummy;
        while (!Q.empty() && prev[sink] == nullptr) {
            int u = Q.front(); Q.pop();
            for (auto& e : graph[u]) {
                if (prev[e.dst] == nullptr && residue(e) > 0) {
                    prev[e.dst] = &e;
                    Q.push(e.dst);
                }
            }
        }
        if (prev[sink] == nullptr) return total;

        // augment flow
        int flow = INT_MAX;
        for (int u = sink; prev[u] != &dummy; u = prev[u]->src)
            flow = min(flow, residue(*prev[u]));
        for (int u = sink; prev[u] != &dummy; u = prev[u]->src) {
            prev[u]->flow += flow;
            prev[u]->rev->flow -= flow;
        }
        total += flow;
    }
}
