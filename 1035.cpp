#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

char floor[110];
char space[110];

int main() {
  int W, Q;
  while (scanf("%d%d", &W, &Q), W|Q) {
    memset(floor, ' ', sizeof(floor));
    memset(space, ' ', sizeof(space));
    map<int, pair<int, int> > id2xw;
    floor[W] = '\0';
    REP(i, Q) {
      char action; scanf(" %c", &action);
      if (action == 's') {
        int id, w; scanf("%d%d", &id, &w);
        space[w] = '\0';
        char* p = strstr(floor, space);
        space[w] = ' ';
        if (p) {
          int x = p - floor;
          printf("%d\n", x);
          REP(j, w) { floor[x+j] = '*'; }
          id2xw.insert(make_pair(id, make_pair(x, w)));
        } else {
          puts("impossible");
        }
      } else if (action == 'w') {
        int id; scanf("%d", &id);
        LET(it, id2xw.find(id));
        int x = it->second.first;
        int w = it->second.second;
        REP(j, w) { floor[x+j] = ' '; }
        id2xw.erase(it);
      } else {
        assert(false);
      }
    }
    puts("END");
  }
}

