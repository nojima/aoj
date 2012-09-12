#include <cstdio>
#include <vector>
#include <map>
using namespace std;

int main() {
  int n, m, a;
  while (scanf("%d%d%d", &n, &m, &a), n|m|a) {
    vector<map<int, int>> bar(1000);
    for (int i = 0; i < m; ++i) {
      int h, p, q; scanf("%d%d%d", &h, &p, &q);
      bar[h-1][p] = q;
      bar[h-1][q] = p;
    }
    for (int i = 999; i >= 0; --i) {
      if (bar[i].count(a)) { a = bar[i][a]; }
    }
    printf("%d\n", a);
  }
}
