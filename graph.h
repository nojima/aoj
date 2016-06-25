template <typename Weight>
struct Edge {
    int src, dst;
    Weight weight;
    Edge(int src, int dst, Weight weight): src(src), dst(dst), weight(weight) {}
    bool operator<(const Edge<Weight>& other) const { return weight < other.weight; }
};
template <typename Weight> using Vertex = vector<Edge<Weight>>;
template <typename Weight> using Graph = vector<Vertex<Weight>>;

template <typename Weight>
double kruskal(const Graph<Weight>& g) {
    UnionFind uf(g.size());

    vector<Edge<Weight>> edges;
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

