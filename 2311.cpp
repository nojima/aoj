#include <cstdio>
#include <cstring>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)

int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
char colors[] = {'o', 'x'};
char field[10][10];

int put(int y, int x, int turn, bool dryrun) {
  int ret = 0;
  REP(dir, 8) {
    int yy = y + dy[dir], xx = x + dx[dir];
    while (field[yy][xx] == colors[!turn]) {
      yy += dy[dir]; xx += dx[dir];
    }
    if (field[yy][xx] == colors[turn]) {
      for (;;) {
        yy -= dy[dir]; xx -= dx[dir];
        if (!dryrun) { field[yy][xx] = colors[turn]; }
        if (yy == y && xx == x) { break; }
        ++ret;
      }
    }
  }
  return ret;
}

int main() {
  memset(field, '.', sizeof(field));
  FOREQ(y, 1, 8) FOREQ(x, 1, 8) {
    scanf(" %c", &field[y][x]);
  }

  for (int turn = 0, pass = 0; pass < 2; turn = !turn) {
    int max_count = 0, arg_max_y = -1, arg_max_x = -1;
    FOREQ(y, 1, 8) FOREQ(x, 1, 8) {
      if (field[y][x] != '.') { continue; }
      int count = put(y, x, turn, true);
      if (count > max_count || (count == max_count && turn == 1)) {
        max_count = count;
        arg_max_y = y;
        arg_max_x = x;
      }
    }
    if (max_count == 0) {
      ++pass;
    } else {
      pass = 0;
      put(arg_max_y, arg_max_x, turn, false);
    }
  }

  FOREQ(y, 1, 8) {
    FOREQ(x, 1, 8) {
      printf("%c", field[y][x]);
    }
    puts("");
  }
}
