#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

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

int bipartie_matching(const Graph& graph, int n_left) {
    vector<int> match(graph.size(), -1);
    int n_match = 0;
    REP(u, n_left) {
        vector<bool> visited(graph.size());
        if (augment(graph, visited, match, u)) ++n_match;
    }
    return n_match;
}

int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a%b); }

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int m, n;
    while (cin>>m>>n, m|n) {
        vector<int> blue(m), red(n);
        REP(i, m) cin >> blue[i];
        REP(i, n) cin >> red[i];

        Graph graph(m+n);
        REP(i, m) REP(j, n) {
            if (gcd(blue[i], red[j]) > 1)
                add_edge(graph, i, m+j);
        }

        cout << bipartie_matching(graph, m) << '\n';
    }
}
