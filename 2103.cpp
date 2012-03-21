#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char field[30][30];

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, -1, 0, 1};
const char dir1[] = {'^', '<', 'v', '>'};
const char dir2[] = {'U', 'L', 'D', 'R'};

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int W, H;
    scanf("%d%d", &H, &W);
    memset(field, '#', sizeof(field));
    int ty, tx, td;
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        scanf(" %c", &field[y][x]);
        for (int k = 0; k < 4; ++k) {
          if (field[y][x] == dir1[k]) {
            ty = y; tx = x; td = k;
            field[y][x] = '.';
            break;
          }
        }
      }
    }

    int N; scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
      char op; scanf(" %c", &op);
      for (int k = 0; k < 4; ++k) {
        if (op == dir2[k]) {
          td = k;
          int ny = ty+dy[k], nx = tx+dx[k];
          if (field[ny][nx] == '.') { ty = ny; tx = nx; }
          break;
        }
      }
      if (op == 'S') {
        int by = ty, bx = tx;
        while (field[by][bx] == '.' || field[by][bx] == '-') {
          by += dy[td]; bx += dx[td];
        }
        if (field[by][bx] == '*') {
          field[by][bx] = '.';
        }
      }
    }

    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        if (ty == y && tx == x) {
          printf("%c", dir1[td]);
        } else {
          printf("%c", field[y][x]);
        }
      }
      puts("");
    }
    if (T > 0) { puts(""); }
  }
}
