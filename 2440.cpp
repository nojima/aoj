#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define REPEQ(i, n) FOREQ(i, 0, n)
#define ALL(c) (c).begin(), (c).end()
#define LET(name, value) __typeof(value) name = (value)

template <typename T> inline int size(const T& x) { return x.size(); }
template <typename T1, typename T2> inline void
updateMax(T1& x, const T2& y) { if (y < x) { x = y; } }
template <typename T1, typename T2> inline void
updateMin(T1& x, const T2& y) { if (x < y) { x = y; } }
template <typename T1, typename T2, typename K1, typename K2> inline void
updateMax(T1& x, K1& i, const T2& y, const K2& j) { if (y < x) { x = y; i = j; } }
template <typename T1, typename T2, typename K1, typename K2> inline void
updateMin(T1& x, K1& i, const T2& y, const K2& j) { if (x < y) { x = y; i = j; } }

int main() {
  cin.tie(0); ios_base::sync_with_stdio(false);

  int N;
  while (cin >> N) {
    vector<string> ids(N);
    REP(i, N) cin >> ids[i];
    sort(ALL(ids));

    int M; cin >> M;
    bool open = false;
    REP(i, M) {
      string id; cin >> id;
      LET(p, equal_range(ALL(ids), id));
      if (p.first != p.second) {
        open = !open;
        if (open) cout << "Opened by " << id << endl;
        else cout << "Closed by " << id << endl;
      } else {
        cout << "Unknown " << id << endl;
      }
    }
  }
}

