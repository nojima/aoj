// Railway Connection
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

const int INF = 1e9;

typedef vector<vector<int>> Matrix;

void WarshallFloyd(Matrix& dist) {
  int n = dist.size();
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}

Matrix dist[30];
int p[30];
int q[30][59];
int r[30][60];
int sum[30][59];

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int n, m, c, s, g;
  while (cin >> n >> m >> c >> s >> g, n | m | c | s | g) {
    --s; --g;

    for (int i = 0; i < c; ++i) {
      dist[i].assign(n, vector<int>(n, INF));
    }

    for (int i = 0; i < m; ++i) {
      int x, y, d, c; cin >> x >> y >> d >> c; --c; --x; --y;
      dist[c][x][y] = min(dist[c][x][y], d);
    }

    for (int i = 0; i < c; ++i) { cin >> p[i]; }

    for (int i = 0; i < c; ++i) {
      for (int j = 0; j < p[i] - 1; ++j) { cin >> q[i][j]; }
      for (int j = 0; j < p[i]; ++j) { cin >> r[i][j]; }

      sum[i][0] = r[i][0] * q[i][0];
      for (int j = 1; j < p[i] - 1; ++j) {
        sum[i][j] = sum[i][j - 1] + r[i][j] * (q[i][j] - q[i][j - 1]);
      }
    }

    for (int i = 0; i < c; ++i) {
      WarshallFloyd(dist[i]);
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          if (dist[i][j][k] < INF) {
            int d = dist[i][j][k];
            auto it = lower_bound(q[i], q[i] + p[i] - 1, d);
            int idx = distance(q[i], it);
            int v = (idx == 0) ? 0 : sum[i][idx - 1];
            int prev_q = (idx == 0) ? 0 : q[i][idx - 1];
            int w = r[i][idx] * (d - prev_q);
            dist[i][j][k] = v + w;
          }
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 1; k < c; ++k) {
          dist[0][i][j] = min(dist[0][i][j], dist[k][i][j]);
        }
      }
    }

    WarshallFloyd(dist[0]);
    int ans = dist[0][s][g];
    if (ans >= INF) {
      cout << -1 << endl;
    } else {
      cout << ans << endl;
    }
  }
}

