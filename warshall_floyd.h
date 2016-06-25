// Verified: AOJ 2251 (Merry Christmas)
vector<vector<Weight>> warshall_floyd(Graph graph) {
    static const Weight inf = numeric_limits<Weight>::max() / 3;
    vector<vector<Weight>> dist(graph.size(), vector<Weight>(graph.size(), inf));
    REP(u, graph.size()) dist[u][u] = 0;
    REP(u, graph.size()) for (auto& e : graph[u]) dist[e.src][e.dst] = e.weight;
    REP(w, graph.size()) REP(u, graph.size()) REP(v, graph.size())
        dist[u][v] = min(dist[u][v], dist[u][w] + dist[w][v]);
    return dist;
}
