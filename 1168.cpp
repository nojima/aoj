#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

struct Piece {
  int left;
  int right;
  int weight;
  int xsum;
  set<Piece*> children;

  Piece(): left(10000), right(-10000), weight(0), xsum(0) {}
};

char field[70][20];
Piece* pieces[70][20];

void dfs(Piece* piece, char mark, int y, int x) {
  static const int dy[] = {-1, 0, 1, 0};
  static const int dx[] = {0, -1, 0, 1};

  piece->weight += 1;
  piece->xsum += x;
  pieces[y][x] = piece;

  REP(i, 4) {
    int ny = y + dy[i], nx = x + dx[i];
    if (field[ny][nx] == '.') { continue; }
    if (field[ny][nx] == mark) {
      if (pieces[ny][nx] == NULL) { dfs(piece, mark, ny, nx); }
    } else if (i == 0) {
      if (pieces[ny][nx] == NULL) {
        dfs(new Piece, field[ny][nx], ny, nx);
      }
      piece->children.insert(pieces[ny][nx]);
    } else if (i == 2) {
      piece->left = min(piece->left, x);
      piece->right = max(piece->right, x+1);
    }
  }
}

inline bool order(int a, int b, int c) {
  return a < b && b < c;
}

bool check(Piece* piece, int& weight, int& xsum) {
  weight = piece->weight;
  xsum = piece->xsum;
  FOREACH(it, piece->children) {
    int w, xs;
    if (!check(*it, w, xs)) { return false; }
    weight += w;
    xsum += xs;
  }
  return order(2*piece->left*weight, 2*xsum+weight, 2*piece->right*weight);
}

int main() {
  int w, h;
  while (scanf("%d%d", &w, &h), w|h) {
    memset(field, '.', sizeof(field));
    memset(pieces, 0, sizeof(pieces));

    FOREQ(x, 1, w) { field[h+1][x] = '#'; }
    FOREQ(y, 1, h) FOREQ(x, 1, w) { scanf(" %c", &field[y][x]); }

    Piece* root = NULL;
    FOREQ(x, 1, w) {
      if (field[h][x] != '.') {
        dfs(new Piece, field[h][x], h, x);
        root = pieces[h][x];
        break;
      }
    }

    int w, xs;
    puts(check(root, w, xs) ? "STABLE" : "UNSTABLE");
  }
}
