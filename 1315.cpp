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

int main() {
  int n;
  while (scanf("%d", &n), n) {
    map<int, int> id2time, id2power;
    REP(i, n) {
      int M, D, h, m, id; char e;
      scanf("%d/%d %d:%d %c %d", &M, &D, &h, &m, &e, &id);
      int time = m + 60 * h;
      if (e == 'I') {
        id2time.insert(make_pair(id, time));
      } else if (e == 'O') {
        int i_time = id2time[id], o_time = time;
        if (id == 0) {
          FOREACH(it, id2time) {
            if (it->first != 0) {
              id2power[it->first] += o_time - max(i_time, it->second);
            }
          }
        } else {
          LET(goddess, id2time.find(0));
          if (goddess != id2time.end()) {
            id2power[id] += o_time - max(i_time, goddess->second);
          }
        }
        id2time.erase(id);
      } else {
        assert(false);
      }
    }
    int ans = 0;
    FOREACH(it, id2power) { ans = max(ans, it->second); }
    printf("%d\n", ans);
  }
}

