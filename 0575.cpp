#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

struct UnionFind {
  vector<int> data;
  explicit UnionFind(int size): data(size, -1) {}
  bool findSet(int x, int y) { return root(x) == root(y); }
  int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
  int size(int x) { return -data[root(x)]; }
  bool unionSet(int x, int y) {
    x = root(x); y = root(y);
    if (x != y) {
      if (data[y] < data[x]) swap(x, y);
      data[x] += data[y];
      data[y] = x;
    }
    return x != y;
  }
};

struct RMQ {
  int n;
  vector<int> data, arg;
  explicit RMQ(const vector<int>& a): n(a.size()), data(n * ceilLog(n)), arg(data.size()) {
    for (int i = 0; i < n; ++i) {
      data[i] = a[i];
      arg[i] = i;
    }
    for (int k = 1, j = 0; k < n; k *= 2, j += n) {
      copy(begin(data) + j, begin(data) + j + n, begin(data) + j + n);
      copy(begin(arg) + j, begin(arg) + j + n, begin(arg) + j + n);
      for (int i = 0; i < n - k; ++i) {
        if (data[i + j] < data[i + j + k]) {
          data[i + j + n] = data[i + j];
          arg[i + j + n] = arg[i + j];
        } else {
          data[i + j + n] = data[i + j + k];
          arg[i + j + n] = arg[i + j + k];
        }
      }
    }
  }
  int query(int x, int y) {
    int z = y - x, k = 0, e = 1, s;
    s = ((z & 0xffff0000) != 0) << 4; z >>= s; e <<= s; k |= s;
    s = ((z & 0x0000ff00) != 0) << 3; z >>= s; e <<= s; k |= s;
    s = ((z & 0x000000f0) != 0) << 2; z >>= s; e <<= s; k |= s;
    s = ((z & 0x0000000c) != 0) << 1; z >>= s; e <<= s; k |= s;
    s = ((z & 0x00000002) != 0) << 0; z >>= s; e <<= s; k |= s;
    int i1 = x + n * k, i2 = y + n * k - e + 1;
    return (data[i1] <= data[i2]) ? arg[i1] : arg[i2];
  }
  int ceilLog(int n) {
    int i = 1;
    for (int k = 1; k < n; k *= 2) ++i;
    return i;
  }
};

struct LCA {
  vector<int> vs, depth, id;
  RMQ rmq;
  LCA(const vector<vector<int>>& tree, int root): id(tree.size()), rmq((dfs(tree, root, 0), depth)) {}
  int query(int u, int v) { return vs[rmq.query(min(id[u], id[v]), max(id[u], id[v]))]; }
  void dfs(const vector<vector<int>>& tree, int v, int d) {
    id[v] = vs.size();
    vs.push_back(v);
    depth.push_back(d);
    for (int w : tree[v]) {
      dfs(tree, w, d + 1);
      vs.push_back(v);
      depth.push_back(d);
    }
  }
};

struct Edge { int src, dst, len; };

struct State {
  int dist, vertex;
  bool operator<(const State& rhs) const { return dist > rhs.dist; }
};

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int N, M, K, P;
  while (cin >> N >> M >> K >> P) {
    vector<vector<Edge>> graph(N + 1);

    for (int i = 0; i < M; ++i) {
      int A, B, L; cin >> A >> B >> L; --A; --B;
      graph[A].push_back({A, B, L});
      graph[B].push_back({B, A, L});
    }

    for (int i = 0; i < K; ++i) {
      int F; cin >> F; --F;
      graph[N].push_back({N, F, 0});
    }

    vector<int> dist(N + 1, INF);
    vector<bool> visit(N + 1);
    priority_queue<State> Q;
    dist[N] = 0;
    Q.push({0, N});
    while (!Q.empty()) {
      int v = Q.top().vertex; Q.pop();
      if (visit[v]) continue;
      visit[v] = true;

      for (auto& e : graph[v]) {
        int newDist = dist[v] + e.len;
        if (dist[e.dst] > newDist) {
          dist[e.dst] = newDist;
          Q.push({newDist, e.dst});
        }
      }
    }

    vector<State> order(N + 1);
    for (int i = 0; i < N + 1; ++i)
      order[i] = { dist[i], i };
    stable_sort(begin(order), end(order));
    UnionFind uf(N + 1);
    vector<int> parent(N + 1, -1);
    vector<int> top(N + 1);
    for (int i = 0; i < N + 1; ++i)
      top[i] = i;
    for (int i = 0; i < N + 1; ++i) {
      int v = order[i].vertex;
      for (auto& e : graph[v]) {
        int w = top[uf.root(e.dst)];
        if (dist[w] > dist[v] || (dist[w] == dist[v] && v > w)) {
          parent[w] = v;
          uf.unionSet(v, w);
          top[uf.root(v)] = v;
        }
      }
    }

    vector<vector<int>> tree(N + 1);
    for (int v = 0; v < N; ++v)
      tree[parent[v]].push_back(v);
    LCA lca(tree, N);

    for (int i = 0; i < P; ++i) {
      int S, T; cin >> S >> T; --S; --T;
      cout << dist[lca.query(S, T)] << endl;
    }
  }
}
