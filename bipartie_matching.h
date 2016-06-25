struct Edge {
    int src, dst;
    Edge(int src, int dst): src(src), dst(dst) {}
};
using Vertex = vector<Edge>;
using Graph = vector<Vertex>;

void add_edge(Graph& graph, int src, int dst) {
    graph[src].emplace_back(src, dst);
    graph[dst].emplace_back(dst, src);
}

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

// Args:
//   graph: 二部グラフ。[0, n_left) が左側の頂点、[n_left, size) が右側の頂点。
//   n_left: 二部グラフの左側の頂点の数。
// Returns:
//   最大マッチングの辺の数
// Verified:
//   AOJ 1163 (Cards), AOJ 2251 (Merry Christmas)
int bipartie_matching(const Graph& graph, int n_left) {
    vector<int> match(graph.size(), -1);
    int n_match = 0;
    REP(u, n_left) {
        vector<bool> visited(graph.size());
        if (augment(graph, visited, match, u)) ++n_match;
    }
    return n_match;
}
