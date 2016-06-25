using Weight = int;
struct Edge {
    int src, dst;
    Weight weight;
    Edge(int src, int dst, Weight weight): src(src), dst(dst), weight(weight) {}
    bool operator<(const Edge& other) const { return weight < other.weight; }
};
using Vertex = vector<Edge>;
using Graph = vector<Vertex>;

double kruskal(const Graph& g) {
    UnionFind uf(g.size());

    vector<Edge> edges;
    for (auto& v : g) edges.insert(edges.end(), v.begin(), v.end());
    sort(edges.begin(), edges.end());

    Weight total = 0;
    for (auto& e : edges) {
        if (uf.merge(e.src, e.dst)) {
            total += e.weight;
        }
    }
    return total;
}
