using Weight = int;
struct Edge {
    int src, dst;
    Weight weight;
};
using Graph = vector<vector<Edge>>;

void add_bidirectional_edge(Graph& graph, int src, int dst, int weight) {
    graph[src].push_back((Edge){src, dst, weight});
    graph[dst].push_back((Edge){dst, src, weight});
}
