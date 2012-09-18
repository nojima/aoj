#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int R, C;
  while (cin >> R >> C, R | C) {
    vector<vector<int>> field(C, vector<int>(R));
    for (int y = 0; y < R; ++y)
      for (int x = 0; x < C; ++x)
        cin >> field[x][y];
    int ans = 0;
    for (int S = 0; S < (1 << R); ++S) {
      int sum = 0;
      for (int x = 0; x < C; ++x) {
        int count = 0;
        for (int y = 0; y < R; ++y)
          count += field[x][y] ^ ((S >> y) & 1);
        sum += max(count, R - count);
      }
      ans = max(ans, sum);
    }
    cout << ans << endl;
  }
}
