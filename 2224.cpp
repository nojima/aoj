#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

inline double sq(double x) { return x*x; }

template <typename Weight>
struct Edge {
    int src, dst;
    Weight weight;
    Edge(int src, int dst, Weight weight): src(src), dst(dst), weight(weight) {}
    bool operator<(const Edge<Weight>& other) const { return weight < other.weight; }
};
template <typename Weight> using Vertex = vector<Edge<Weight>>;
template <typename Weight> using Graph = vector<Vertex<Weight>>;

struct UnionFind {
    vector<int> data;
    explicit UnionFind(int size): data(size, -1) {}
    bool merge(int x, int y) {
        x = root(x); y = root(y);
        if (x != y) {
            if (data[y] < data[x]) swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        return x != y;
    }
    bool find(int x, int y) { return root(x) == root(y); }
    int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
};

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

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int N, M;
    while (cin>>N>>M) {
        vector<pair<int, int>> piles(N), fances(M);
        REP(i, N) cin >> piles[i].first >> piles[i].second;
        REP(i, M) {
            cin >> fances[i].first >> fances[i].second;
            --fances[i].first; --fances[i].second;
        }

        Graph<double> g(N);
        double total = 0;
        REP(i, M) {
            auto& p1 = piles[fances[i].first];
            auto& p2 = piles[fances[i].second];
            double length = sqrt(sq(p1.first - p2.first) + sq(p1.second - p2.second));
            g[fances[i].first].emplace_back(fances[i].first, fances[i].second, -length);
            total += length;
        }

        double w = -kruskal(g);
        cout << setprecision(10) << total - w << '\n';
    }
}
