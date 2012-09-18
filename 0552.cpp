#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

#define FOR(i, k, n) for (int i = (k); i < (int)(n); ++i)
#define REP(i, n) FOR(i, 0, n)

typedef pair<int, int> pii;
typedef priority_queue<pii, vector<pii>, less<pii>> PQL;
typedef priority_queue<pii, vector<pii>, greater<pii>> PQG;

vector<int> assignment;
vector<pii> points;
PQL maxQueue[3][4];
PQG minQueue[3][4];

int f(const pii& p, int k) {
  static const int dx[] = {-1, -1, 1, 1};
  static const int dy[] = {1, -1, 1, -1};
  return p.first * dx[k] + p.second * dy[k];
}

void assign(int p, int j) {
  assignment[p] = j;
  REP(k, 4) {
    maxQueue[j][k].push(make_pair(f(points[p], k), p));
    minQueue[j][k].push(make_pair(f(points[p], k), p));
  }
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int n; cin >> n;
  points.resize(n);
  REP(i, n) cin >> points[i].first >> points[i].second;

  int answer = INT_MAX;
  for (int dir = 0; dir < 2; ++dir) {
    assignment.assign(n, -1);
    REP(i, 3) REP(j, 4) maxQueue[i][j] = PQL(), minQueue[i][j] = PQG();

    REP(i, n) REP(k, 4) {
      maxQueue[0][k].push(make_pair(f(points[i], k), i));
      minQueue[0][k].push(make_pair(f(points[i], k), i));
    }

    while (!maxQueue[0][0].empty()) {
      int maxDist = -1, argMaxJ = -1, argMaxK = -1;
      REP(j, 3) {
        if (maxQueue[j][0].empty()) continue;
        REP(k, 4) {
          int dist = maxQueue[j][k].top().first - minQueue[0][k].top().first;
          if (dist > maxDist) {
            maxDist = dist;
            argMaxJ = j;
            argMaxK = k;
          }
        }
      }

      if (argMaxJ == 0) {
        int p[2] = { maxQueue[0][argMaxK].top().second, minQueue[0][argMaxK].top().second };
        int maxDist[2] = {-1, -1};
        REP(l, 2) FOR(j, 1, 3) REP(k, 4) {
          auto& pt = points[p[(l + j - 1) % 2]];
          int maxV = (maxQueue[j][k].empty() ? INT_MIN : maxQueue[j][k].top().first);
          int minV = (minQueue[j][k].empty() ? INT_MAX : minQueue[j][k].top().first);
          maxDist[l] = max(maxDist[l], max(maxV, f(pt, k)) - min(minV, f(pt, k)));
        }

        int r = (maxDist[0] < maxDist[1]) ? 0 : 1;
        if (dir == 1) r = 1 - r;
        assign(p[0], r + 1);
        assign(p[1], 2 - r);
      } else {
        assign(minQueue[0][argMaxK].top().second, 3 - argMaxJ);
      }

      REP(k, 4) {
        while (!maxQueue[0][k].empty() && assignment[maxQueue[0][k].top().second] != -1)
          maxQueue[0][k].pop();
        while (!minQueue[0][k].empty() && assignment[minQueue[0][k].top().second] != -1)
          minQueue[0][k].pop();
      }
    }

    int ans = -1;
    FOR(j, 1, 3) REP(k, 4)
      ans = max(ans, maxQueue[j][k].top().first - minQueue[j][k].top().first);
    answer = min(answer, ans);
  }
  cout << answer << endl;
}
