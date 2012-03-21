#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <queue>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

int time[50], laps[50], limit[2];

struct Entry {
  int id, lane, t;
  Entry(int id, int lane, int t): id(id), lane(lane), t(t) {}
  bool operator<(const Entry& rhs) const {
    return (t == rhs.t) ? (time[id] > time[rhs.id]) : (t > rhs.t);
  }
};

int main() {
  int n;
  while (scanf("%d", &n), n) {
    limit[0] = limit[1] = 0;
    REP(i, n) { scanf("%d%d", time+i, laps+i); laps[i] *= 2; }
    priority_queue<Entry> Q;
    REP(i, n) { Q.push(Entry(i, 0, 0)); }
    while (!Q.empty()) {
      int id = Q.top().id;
      int lane = Q.top().lane;
      int t = Q.top().t;
      Q.pop();
      limit[lane] = max(limit[lane], t + time[id]);
      --laps[id];
      if (laps[id] > 0) { Q.push(Entry(id, !lane, limit[lane])); }
    }
    printf("%d\n", max(limit[0], limit[1]));
  }
}
