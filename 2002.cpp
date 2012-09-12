#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <cstdio>
using namespace std;

template <typename F>
inline void update(map<char, int>& m, char key, int val, F f) {
  if (m.count(key)) {
    m[key] = f(m[key], val);
  } else {
    m[key] = val;
  }
}

bool solve() {
  typedef const int& (*F)(const int&, const int&);
  int H, W; scanf("%d%d", &H, &W);
  vector<string> field(H, string(W, '.'));
  for (int y = 0; y < H; ++y) {
    for (int x = 0; x < W; ++x) {
      scanf(" %c", &field[y][x]);
    }
  }
  for (;;) {
    map<char, int> left, right, top, bottom;
    bool end = true;
    for (int y = 0; y < H; ++y) {
      for (int x = 0; x < W; ++x) {
        const char ch = field[y][x];
        if (ch != '.' && ch != '*') {
          update(left, ch, x, (F)min);
          update(top, ch, y, (F)min);
          update(right, ch, x, (F)max);
          update(bottom, ch, y, (F)max);
          end = false;
        }
      }
    }
    if (end) { return true; }
    bool bad = true;
    for (auto p : left) {
      const char ch = p.first;
      const int l = p.second, r = right[ch], t = top[ch], b = bottom[ch];
      bool ok = true;
      for (int y = t; y <= b; ++y) {
        for (int x = l; x <= r; ++x) {
          if (field[y][x] != ch && field[y][x] != '*') {
            ok = false;
            break;
          }
        }
      }
      if (ok) {
        for (int y = t; y <= b; ++y) {
          for (int x = l; x <= r; ++x) {
            field[y][x] = '*';
          }
        }
        bad = false;
        break;
      }
    }
    if (bad) { return false; }
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    puts(solve() ? "SAFE" : "SUSPICIOUS");
  }
}
