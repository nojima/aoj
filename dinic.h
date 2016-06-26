struct Edge {
    int src, dst, capacity;
};
using Graph = vector<vector<Edge>>;

void add_edge(Graph& graph, int src, int dst, int capacity) {
    graph[src].push_back((Edge){src, dst, capacity});
    graph[dst].push_back((Edge){dst, src, 0});
}

struct Augment {
    const Graph graph;
    const vector<int>& level;
    vector<vector<int>>& flow;
    vector<int>& progress;
    int sink;
    int operator()(int u, int f) const {
        if (u == sink) return f;
        int total = 0, i = progress[u];
        for (; i < (int)graph[u].size(); ++i) {
            auto& e = graph[u][i];
            int residue = e.capacity - flow[e.src][e.dst];
            if (residue > 0 && level[e.src] < level[e.dst]) {
                int aug = (*this)(e.dst, min(f - total, residue));
                flow[e.src][e.dst] += aug;
                flow[e.dst][e.src] -= aug;
                total += aug;
                if (total == f) break;
            }
        }
        progress[u] = i;
        return total;
    }
};

// Verified: AOJ GRL_6_A (Maximum Flow)
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
        total += (Augment){graph, level, flow, progress, sink}(source, INT_MAX);
    }
}
