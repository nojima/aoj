#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1e7;

struct Edge {
  int src, dst, cap, flow, id;
  bool reversed;
};

typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

int augment(Graph& graph, vector<vector<Edge*>>& rev,
            vector<int>& level, vector<bool>& finish, int u, int t, int cur) {
  if (u == t || cur == 0) return cur;
  if (finish[u]) return 0;
  finish[u] = true;

  for (Edge& e : graph[u]) {
    if (level[e.dst] > level[u]) {
      int f = augment(graph, rev, level, finish, e.dst, t, min(cur, e.cap - e.flow));
      if (f > 0) {
        e.flow += f;
        finish[u] = false;
        return f;
      }
    }
  }

  for (Edge* e : rev[u]) {
    if (level[e->dst] > level[u]) {
      int f = augment(graph, rev, level, finish, e->dst, t, min(cur, e->flow));
      if (f > 0) {
        e->flow -= f;
        finish[u] = false;
        return f;
      }
    }
  }

  return 0;
}

// Dinic
int maxFlow(Graph& graph, int s, int t) {
  int n = graph.size(), total = 0;

  vector<vector<Edge*>> rev(n);
  for (int u = 0; u < n; ++u)
    for (Edge& e : graph[u])
      rev[e.dst].push_back(&e);

  for (bool cont = true; cont; ) {
    cont = false;

    vector<int> level(n, -1);
    level[s] = 0;

    queue<int> Q;
    Q.push(s);

    for (int d = n; !Q.empty() && level[Q.front()] < d; ) {
      int u = Q.front(); Q.pop();
      if (u == t) d = level[u];
      for (const Edge& e : graph[u]) {
        if (e.cap - e.flow > 0 && level[e.dst] == -1) {
          Q.push(e.dst);
          level[e.dst] = level[u] + 1;
        }
      }
      for (const Edge* e : rev[u]) {
        if (e->flow > 0 && level[e->dst] == -1) {
          Q.push(e->dst);
          level[e->dst] = level[u] + 1;
        }
      }
    }

    vector<bool> finish(n, false);
    for (;;) {
      int f = augment(graph, rev, level, finish, s, t, INF);
      if (f == 0) break;
      total += f;
      cont = true;
    }
  }

  return total;
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int N, M;
  while (cin >> N >> M) {
    Graph graph(N);
    for (int i = 0; i < M; ++i) {
      int X, Y; cin >> X >> Y; --X; --Y;
      graph[X].push_back({X, Y, 1, 0, i, false});
      graph[Y].push_back({Y, X, 1, 0, i, true});
    }
    int S, T; cin >> S >> T; --S; --T;
    int value = maxFlow(graph, S, T);

    vector<int> answer;
    for (int u = 0; u < N; ++u)
      for (const Edge& e : graph[u])
        if (e.flow > 0 && e.reversed)
          answer.push_back(e.id + 1);
    sort(answer.begin(), answer.end());

    cout << value << endl << answer.size() << endl;
    for (int id : answer)
      cout << id << endl;
  }
}
