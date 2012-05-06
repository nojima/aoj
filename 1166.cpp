#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

vector<int> adj[910];
int cost[910];

inline void add_edge(int s, int t) {
  adj[s].push_back(t);
  adj[t].push_back(s);
}

int main() {
  int w, h;
  while (scanf("%d%d", &w, &h), w|h) {
    REP(i, w*h) { adj[i].clear(); }
    memset(cost, 0, sizeof(cost));

    REP(y, 2*h-1) {
      REP(x, w+y%2-1) {
        int d; scanf("%d", &d);
        if (d == 0) {
          if (y%2 == 0) {
            add_edge((y/2)*w+x, (y/2)*w+x+1);
          } else {
            add_edge((y/2)*w+x, (y/2+1)*w+x);
          }
        }
      }
    }

    queue<int> Q;
    cost[0] = 1;
    Q.push(0);
    while (!Q.empty()) {
      int v = Q.front(); Q.pop();
      if (v == w*h-1) { break; }
      FOREACH(it, adj[v]) {
        int u = *it;
        if (cost[u] == 0) {
          cost[u] = cost[v]+1;
          Q.push(u);
        }
      }
    }

    printf("%d\n", cost[w*h-1]);
  }
}
