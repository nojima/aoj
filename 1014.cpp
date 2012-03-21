#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

struct Edge {
  int s, t, w;
  Edge(int s, int t, int w): s(s), t(t), w(w) {}
  bool operator<(const Edge& rhs) const { return w < rhs.w; }
};

struct UnionFind {
  vector<int> data;
  UnionFind(int size): data(size, -1) {}
  bool merge(int x, int y) {
    x = root(x); y = root(y);
    if (x != y) {
      if (data[y] < data[x]) { swap(x, y); }
      data[x] += data[y]; data[y] = x;
    }
    return x != y;
  }
  int root(int x) {
    return data[x] < 0 ? x : data[x] = root(data[x]);
  }
};

int minimum_spanning_tree(vector<Edge>& edges) {
  sort(ALL(edges));
  UnionFind uf(edges.size());
  int w = 0;
  REP(i, edges.size()) {
    Edge e = edges[i];
    int r1 = uf.root(e.s), r2 = uf.root(e.t);
    if (r1 != r2) {
      uf.merge(r1, r2);
      w += e.w;
    }
  }
  return w;
}

vector<Edge> edges;

int main() {
  int s, d;
  while (scanf("%d%d", &s, &d), s|d) {
    edges.clear();
    REP(i, s) REP(j, d) {
      int w; scanf("%d", &w);
      if (w > 0) { edges.push_back(Edge(i, s+j, w)); }
    }
    REP(i, d-1) FOR(j, i+1, d) {
      int w; scanf("%d", &w);
      if (w > 0) { edges.push_back(Edge(s+i, s+j, w)); }
    }
    REP(i, s) FOR(j, i+1, s) {
      edges.push_back(Edge(i, j, 0));
    }
    printf("%d\n", minimum_spanning_tree(edges));
  }
}
