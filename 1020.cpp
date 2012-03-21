#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <climits>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREACH(i, c) for (__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, -1, 0, 1};
double prob[20][3][3];

int main()
{
  int n;
  while (scanf("%d", &n), n) {
    memset(prob, 0, sizeof(prob));
    char cs, ct, cb;
    scanf(" %c %c %c", &cs, &ct, &cb);
    int s = cs - 'A', t = ct - 'A', b = cb - 'A';
    prob[0][s / 3][s % 3] = 1.0;
    for (int i = 0; i < n; ++i) {
      for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
          for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= 3 || nx < 0 || nx >= 3) { ny = y; nx = x; }
            if (ny == b / 3 && nx == b % 3) { ny = y; nx = x; }
            prob[i+1][ny][nx] += 0.25 * prob[i][y][x];
          }
        }
      }
    }
    printf("%.9lf\n", prob[n][t / 3][t % 3]);
  }
}
