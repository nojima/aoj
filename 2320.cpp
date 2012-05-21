#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
const char* dir_str = "NESW";
char field[110][110];
long long steps[4][110][110];

int main() {
  int H, W;
  long long L;
  while (scanf("%d%d%lld", &H, &W, &L), H|W|L) {
    memset(field, '#', sizeof(field));
    memset(steps, -1, sizeof(steps));

    int sy = -1, sx = -1, sdir = -1;
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        scanf(" %c", &field[y][x]);
        if (isalpha(field[y][x])) {
          switch (field[y][x]) {
          case 'N': sdir = 0; break;
          case 'E': sdir = 1; break;
          case 'S': sdir = 2; break;
          case 'W': sdir = 3; break;
          }
          field[y][x] = '.';
          sy = y; sx = x;
        }
      }
    }

    int yy = sy, xx = sx, dir = sdir;
    for (long long k = 0; k < L; ++k) {
      if (steps[dir][yy][xx] == -1) {
        steps[dir][yy][xx] = k;
      } else {
        long long rest = L - k;
        long long period = k - steps[dir][yy][xx];
        k = L - rest % period;
        if (k == L) { break; }
      }

      int ny = yy + dy[dir], nx = xx + dx[dir];
      while (field[ny][nx] == '#') {
        dir = (dir + 1) % 4;
        ny = yy + dy[dir]; nx = xx + dx[dir];
      }
      yy = ny; xx = nx;
    }

    printf("%d %d %c\n", yy, xx, dir_str[dir]);
  }
}
