#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

enum State { NG, OK, UNKNOWN };

int main() {
  int a, b, c;
  while (cin >> a >> b >> c, a | b | c) {
    vector<State> states[3] = {
      vector<State>(a, UNKNOWN), vector<State>(b, UNKNOWN), vector<State>(c, UNKNOWN) };
    vector<vector<int>> failed;
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
      int x, y, z, r; cin >> x >> y >> z >> r; --x; --y; --z; y -= a; z -= a+b;
      if (r)
        states[0][x] = OK, states[1][y] = OK, states[2][z] = OK;
      else
        failed.push_back({x, y, z});
    }
    for (const vector<int>& f : failed) {
      int count = 0;
      for (int i = 0; i < 3; ++i)
        if (states[i][f[i]] == OK)
          ++count;
      if (count == 2)
        for (int i = 0; i < 3; ++i)
          if (states[i][f[i]] != OK)
            states[i][f[i]] = NG;
    }
    for (auto s : states)
      for (int v : s)
        cout << v << endl;
  }
}
