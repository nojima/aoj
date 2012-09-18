#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int table[6][7] = {
  {-1, 2, 6, 3, 4, 1, 5},
  {-1, 4, 2, 1, 6, 5, 3},
  {-1, 3, 2, 6, 1, 5, 4},
  {-1, 5, 1, 3, 4, 6, 2},
  {-1, 1, 3, 5, 2, 4, 6},
  {-1, 1, 4, 2, 5, 3, 6},
};

vector<int> rotate(const vector<int>& dice, int op) {
  vector<int> next(7);
  for (int i = 1; i <= 6; ++i)
    next[i] = dice[table[op][i]];
  return next;
}

int main() {
  int n;
  while (cin >> n, n) {
    vector<int> dice{-1, 1, 2, 3, 4, 5, 6};
    int ans = 1;
    for (int i = 0; i < n; ++i) {
      string operation; cin >> operation;
      if (operation == "North")
        dice = rotate(dice, 0);
      else if (operation == "East")
        dice = rotate(dice, 1);
      else if (operation == "West")
        dice = rotate(dice, 2);
      else if (operation == "South")
        dice = rotate(dice, 3);
      else if (operation == "Right")
        dice = rotate(dice, 4);
      else if (operation == "Left")
        dice = rotate(dice, 5);
      else
        assert(false);
      ans += dice[1];
    }
    cout << ans << endl;
  }
}
