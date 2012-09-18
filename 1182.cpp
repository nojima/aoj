#include <algorithm>
#include <climit>
#include <iostream>
#include <vector>
using namespace std;

int stationCount, lineCount, companyCount, startStation, targetStation;

typedef vector<vector<long long>> Matrix;

Matrix folydWarshall(const Matrix& g) {
  int n = g.size();
  Matrix dist(g);
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
  return dist;
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  while (cin >> stationCount >> lineCount >> companyCount >> startStation >> targetStation, stationCount) {
    vector<Matrix> graphs(companyCount,
        Matrix(stationCount, vector<long long>(stationCount, INT_MAX)));
    for (int i = 0; i < companyCount; ++i)
      for (int j = 0; j < stationCount; ++j)
        graphs[i][j][j] = 0;
    for (int i = 0; i < lineCount; ++i) {
      int x, y, d, c;
      cin >> x >> y >> d >> c;
      graphs[c][i][j] = graphs[c][j][i] = min(graphs[c][i][j], d);
    }
    for (int i = 0; i < companyCount; ++i) {
      Matrix dist(folydWarshall(graphs[i]));
    }
  }
}
