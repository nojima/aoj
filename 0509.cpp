#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define ALL(c) begin(c), end(c)

struct Event {
  int type, x1, x2, y;
  bool operator<(const Event& rhs) const { return y < rhs.y; }
};

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int n, r;
  while (cin >> n >> r, n | r) {
    vector<Event> events;
    int W = 0, H = 0;
    for (int i = 0; i < n; ++i) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      ++x1; ++y1; ++x2; ++y2;
      events.push_back({+1, x1, x2, y1});
      events.push_back({-1, x1, x2, y2});
      W = max(W, x2 + 1);
      H = max(H, y2 + 1);
    }
    sort(ALL(events));

    vector<vector<int>> field(2, vector<int>(W));
    int area = 0, perimeter = 0;
    for (int y = 1, k = 0; y < H; ++y) {
      int curr = y % 2, prev = (y - 1) % 2;
      field[curr] = field[prev];
      for (; k < (int)events.size() && events[k].y == y; ++k) {
        auto& e = events[k];
        for (int x = e.x1; x < e.x2; ++x)
          field[curr][x] += e.type;
      }
      for (int x = 1; x < W; ++x) {
        int b = !!field[curr][x];
        area += b;
        perimeter += (!!field[curr][x-1] ^ b) + (!!field[prev][x] ^ b);
      }
    }

    if (r == 1)
      cout << area << endl;
    else
      cout << area << endl << perimeter << endl;
  }
}
