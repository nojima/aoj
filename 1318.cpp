#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

struct Edge {
  int dst, dist;
  Edge(int dst, int dist): dst(dst), dist(dist) {}
};

struct State {
  int city, rest, cost;
  State(int city, int rest, int cost): city(city), rest(rest), cost(cost) {}
  bool operator<(const State& rhs) const { return cost > rhs.cost; }
};

inline int add_name(map<string, int>& name2id, const string& name) {
  if (name2id.count(name)) {
    return name2id[name];
  } else {
    int id = name2id.size();
    return name2id[name] = id;
  }
}

vector<Edge> edges[6010];
bool has_lpg[6010];
bool visit[6010][2010];
int cost[6010][2010];

int main() {
  int N, M, cap;
  while (scanf("%d%d%d", &N, &M, &cap), N|M|cap) {
    map<string, int> name2id;
    string src_name, dst_name;

    memset(has_lpg, false, sizeof(has_lpg));
    memset(visit, false, sizeof(visit));
    memset(cost, 0x0f, sizeof(cost));

    cin >> src_name >> dst_name;
    int src = add_name(name2id, src_name);
    int dst = add_name(name2id, dst_name);
    REP(i, N) {
      int dist;
      cin >> src_name >> dst_name >> dist;
      int s = add_name(name2id, src_name);
      int t = add_name(name2id, dst_name);
      edges[s].push_back(Edge(t, dist));
      edges[t].push_back(Edge(s, dist));
    }
    REP(i, M) {
      cin >> src_name;
      has_lpg[name2id[src_name]] = true;
    }

    priority_queue<State> Q;
    Q.push(State(src, 10 * cap, 0));
    cost[src][10 * cap] = 0;
    int ans = -1;

    while (!Q.empty()) {
      int city = Q.top().city;
      int rest = Q.top().rest;
      Q.pop();

      if (visit[city][rest]) { continue; }
      visit[city][rest] = true;
      if (city == dst) {
        ans = cost[city][rest];
        break;
      }

      FOREACH(it, edges[city]) {
        int new_city = it->dst;
        if (rest < it->dist) { continue; }
        int new_rest = has_lpg[new_city] ? 10 * cap : rest - it->dist;
        int new_cost = cost[city][rest] + it->dist;
        if (new_cost >= cost[new_city][new_rest]) { continue; }
        cost[new_city][new_rest] = new_cost;
        Q.push(State(new_city, new_rest, new_cost));
      }
    }

    cout << ans << endl;

    REP(i, name2id.size()) { edges[i].clear(); }
  }
}
