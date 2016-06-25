// Not verified.
vector<Weight> bellman_ford(const Graph& graph, int source) {
    static const Weight inf = numeric_limits<Weight>::max() / 3;
    vector<Weight> dist(graph.size(), inf);
    dist[source] = 0;
    for (int i = 0; ; ++i) {
        bool updated = false;
        REP(u, graph.size()) {
            if (dist[u] == inf) continue;
            for (auto& e : graph[u]) {
                if (dist[e.dst] > dist[e.src] + e.weight) {
                    dist[e.dst] = dist[e.src] + e.weight;
                    updated = true;
                }
            }
        }
        if (!updated) return dist;
        if (i == int(graph.size())) assert(false);  // the graph has a negative cycle
    }
}
