#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

char field[30][30];

int main() {
  int h, w;
  while (scanf("%d%d", &h, &w), h|w) {
    REP(y, h) REP(x, w) { scanf(" %c", &field[y][x]); }

    static const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    set<string> dict;
    string ans, str;
    REP(sy, h) REP(sx, w) REP(dir, 8) {
      int y = sy, x = sx;
      str.clear();
      do {
        str += field[y][x];
        LET(it, dict.lower_bound(str));
        if (it != dict.end() && *it == str) {
          if (str.size() > ans.size() || (str.size() == ans.size() && str < ans)) {
            ans = str;
          }
        } else {
          dict.insert(it, str);
        }
        y = (y + dy[dir] + h) % h;
        x = (x + dx[dir] + w) % w;
      } while (y != sy || x != sx);
    }
    printf("%s\n", ans.size() > 1 ? ans.c_str() : "0");
  }
}

