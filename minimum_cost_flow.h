using Weight = int;
struct Edge {
    int src, dst, capacity;
    Weight weight;
    Edge(int src, int dst, int capacity, Weight weight): src(src), dst(dst), capacity(capacity), weight(weight) {}
    bool operator<(const Edge& other) const { return weight < other.weight; }
};
using Graph = vector<vector<Edge>>;

void add_edge(Graph& graph, int src, int dst, int capacity, Weight weight) {
    graph[src].emplace_back(src, dst, capacity, weight);
    graph[dst].emplace_back(dst, src, 0, -weight);
}

// Verified: AOJ 2293 (Dangerous Tower)
Weight minimum_cost_flow(const Graph& graph, int source, int sink) {
    static const Weight inf = numeric_limits<Weight>::max() / 3;
    vector<vector<int>> flow(graph.size(), vector<int>(graph.size()));

    // calculate initial potential with Bellman Ford.
    vector<Weight> potential(graph.size(), inf);
    potential[source] = 0;
    for (int i = 0; ; ++i) {
        bool updated = false;
        REP(u, graph.size()) {
            if (potential[u] == inf) continue;
            for (auto& e : graph[u]) {
                if (e.capacity > 0 && potential[e.dst] > potential[e.src] + e.weight) {
                    potential[e.dst] = potential[e.src] + e.weight;
                    updated = true;
                }
            }
        }
        if (!updated) break;
        if (i == int(graph.size())) assert(false);  // the graph has a negative cycle
    }

    Weight total = 0;
    for (;;) {
        // find path
        using State = pair<Weight, int>;  // (distance, vertex)
        priority_queue<State, vector<State>, greater<State>> Q;
        vector<Weight> dist(graph.size(), inf);
        vector<const Edge*> prev(graph.size(), nullptr);
        Q.push(State(0, source));
        dist[source] = 0;
        while (!Q.empty()) {
            Weight w; int u; tie(w, u) = Q.top(); Q.pop();
            if (dist[u] < w) continue;
            for (auto& e : graph[u]) {
                int residue = e.capacity - flow[e.src][e.dst];
                int cost = e.weight + potential[e.src] - potential[e.dst];
                if (residue > 0 && dist[e.dst] > dist[e.src] + cost) {
                    dist[e.dst] = dist[e.src] + cost;
                    prev[e.dst] = &e;
                    Q.push(State(dist[e.dst], e.dst));
                }
            }
        }
        if (prev[sink] == nullptr) return total;
        REP(u, graph.size()) potential[u] += dist[u];

        // augment flow
        int aug = INT_MAX;
        for (int v = sink; prev[v] != nullptr; v = prev[v]->src) {
            auto e = prev[v];
            aug = min(aug, e->capacity - flow[e->src][e->dst]);
        }
        for (int v = sink; prev[v] != nullptr; v = prev[v]->src) {
            auto e = prev[v];
            flow[e->src][e->dst] += aug;
            flow[e->dst][e->src] -= aug;
        }
        total += aug * potential[sink];
    }
}
