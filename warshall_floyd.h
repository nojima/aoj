using Weight = int;
struct Edge {
    int src, dst;
    Weight weight;
    Edge(int src, int dst, Weight weight): src(src), dst(dst), weight(weight) {}
};
using Vertex = vector<Edge>;
using Graph = vector<Vertex>;

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
