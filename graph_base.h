using Weight = int;
struct Edge {
    int src, dst;
    Weight weight;
    Edge(int src, int dst, Weight weight): src(src), dst(dst), weight(weight) {}
    bool operator<(const Edge& other) const { return weight < other.weight; }
};
using Graph = vector<vector<Edge>>;
