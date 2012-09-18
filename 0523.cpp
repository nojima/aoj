#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
using namespace std;

#define ALL(c) begin(c), end(c)

int main() {
  int n;
  while (cin >> n, n) {
    vector<int> players[2];
    for (int i = 0; i < n; ++i) {
      int c; cin >> c; --c;
      players[0].push_back(c);
    }
    sort(ALL(players[0]));
    vector<int> all(2*n);
    for (int i = 0; i < 2*n; ++i)
      all[i] = i;
    set_difference(ALL(all), ALL(players[0]), back_inserter(players[1]));

    int play = -1;
    for (int turn = 0; ; turn = !turn) {
      vector<int>& player = players[turn];
      auto it = lower_bound(ALL(player), play);
      if (it == player.end()) {
        play = -1;
      } else {
        play = *it;
        player.erase(it);
        if (player.empty())
          break;
      }
    }

    cout << players[1].size() << endl << players[0].size() << endl;
  }
}
