#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

int main() {
  int n, r;
  while (cin >> n >> r, n|r) {
    vector<int> deck(n);
    REP(i, n) { deck[i] = n - i; }
    REP(i, r) {
      int p, c; cin >> p >> c;
      reverse(deck.begin(), deck.begin() + p + c - 1);
      reverse(deck.begin(), deck.begin() + c);
      reverse(deck.begin() + c, deck.begin() + p + c - 1);
    }
    cout << deck.front() << endl;
  }
}

