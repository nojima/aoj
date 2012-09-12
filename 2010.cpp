#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <queue>
#include <cassert>
using namespace std;

const long long INF = 1e10;
typedef vector<vector<long long>> Matrix;

struct Event {
  long long time;
  function<void ()> proc;

  Event(long long time, function<void ()> proc): time(time), proc(proc) {}
  bool operator<(const Event& rhs) const { return time > rhs.time; }
};

struct Packet {
  int src, dst;
  string name;

  Packet(int src, int dst, const string& name): src(src), dst(dst), name(name) {}
};

enum OfficeState { FREE, BUSY };

struct Office {
  OfficeState state;
  multimap<pair<int, int>, Packet> packets;

  Office(): state(FREE) {}
};

Matrix shortestPath(const Matrix& g) {
  int n = g.size();
  Matrix dist(g);
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
  return dist;
}

int nextVertex(const Matrix& g, const Matrix& dist, int s, int t) {
  int n = dist.size();
  for (int v = 0; v < n; ++v)
    if (v != s && g[s][v] + dist[v][t] == dist[s][t])
      return v;
  assert(false);
}

int n, m;
Matrix g, dist;
vector<Office> offices;
vector<pair<int, string>> result;
priority_queue<Event> Q;

void onReturn(int time, int office) {
  offices[office].state = FREE;
}

void onReceive(int time, int office, const vector<Packet>& packets) {
  Office& o = offices[office];
  for (auto packet : packets) {
    if (packet.dst == office) {
      result.push_back({time, packet.name});
    } else {
      int next = nextVertex(g, dist, office, packet.dst);
      o.packets.insert({{time, next}, packet});
    }
  }
}

void deliver(int time, int office) {
  Office& o = offices[office];
  if (o.state == BUSY || o.packets.empty()) return;
  o.state = BUSY;
  int next = o.packets.begin()->first.second;
  int t1 = time + g[office][next];
  int t2 = t1 + g[office][next];
  vector<Packet> ps;
  for (auto it = o.packets.begin(); it != o.packets.end(); ) {
    if (it->first.second == next) {
      ps.push_back(it->second);
      it = o.packets.erase(it);
    } else {
      ++it;
    }
  }
  Q.push({t1, bind(onReceive, t1, next, ps)});
  Q.push({t2, bind(onReturn, t2, office)});
}

int main() {
  for (int T = 0; cin >> n >> m, n | m; ++T) {
    if (T > 0) { cout << endl; }
    result.clear();
    g.assign(n, vector<long long>(n, INF));

    for (int i = 0; i < m; ++i) {
      int a, b, c; cin >> a >> b >> c; --a; --b;
      g[a][b] = g[b][a] = c;
    }
    for (int i = 0; i < n; ++i)
      g[i][i] = 0;

    dist = shortestPath(g);
    offices.assign(n, Office());

    int l; cin >> l;
    for (int i = 0; i < l; ++i) {
      int src, dst;
      long long time;
      string name;
      cin >> src >> dst >> time >> name; --src; --dst;
      Q.push({time, bind(onReceive, time, src, vector<Packet>{{src, dst, name}})});
    }

    while (!Q.empty()) {
      int time = Q.top().time;
      do {
        Event e = Q.top(); Q.pop();
        e.proc();
      } while (!Q.empty() && Q.top().time == time);
      for (int i = 0; i < n; ++i)
        deliver(time, i);
    }

    sort(result.begin(), result.end());
    for (auto p : result)
      cout << p.second << " " << p.first << endl;
  }
}
