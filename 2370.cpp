#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> Edges;
typedef vector<Edges> Graph;

int main() {
  int V, E;
  while (scanf("%d%d", &V, &E) != EOF) {
    Graph g(V);
    vector<int> color(V);
    for (int i = 0; i < E; ++i) {
      int a, b; scanf("%d%d", &a, &b); --a; --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }
  }
}
