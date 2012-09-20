#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll INF = 1e15;

struct P {
  ll x, y;
  bool operator<(const P& rhs) const {
    return (x == rhs.x) ? (y < rhs.y) : (x < rhs.x);
  }
};

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  ll W, H;
  int N;
  while (cin >> W >> H >> N) {
    vector<P> ps(N);
    vector<ll> xsorted(N), ysorted(N);
    for (int i = 0; i < N; ++i) {
      cin >> ps[i].x >> ps[i].y;
      xsorted[i] = ps[i].x;
      ysorted[i] = ps[i].y;
    }
    sort(begin(xsorted), end(xsorted));
    sort(begin(ysorted), end(ysorted));
    vector<P> candidates;
    for (int i = 0; i < min(3, N); ++i) {
      for (int j = 0; j < min(3, N); ++j) {
        candidates.push_back({xsorted[(N - 1) / 2 + (i + 1) % 3 - 1],
                              ysorted[(N - 1) / 2 + (j + 1) % 3 - 1]});
      }
    }
    pair<ll, P> ans = {INF, {INF, INF}};
    for (P c : candidates) {
      ll maxDist = -1, totalDist = 0;
      for (int i = 0; i < N; ++i) {
        ll dist = abs(ps[i].x - c.x) + abs(ps[i].y - c.y);
        totalDist += dist;
        maxDist = max(maxDist, dist);
      }
      ans = min(ans, make_pair(2 * totalDist - maxDist, c));
    }
    cout << ans.first << endl << ans.second.x << " " << ans.second.y << endl;
  }
}
