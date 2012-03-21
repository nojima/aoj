#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <deque>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

int main() {
  int n, r;
  while (scanf("%d%d", &n, &r) != EOF) {
    deque<int> deck0, deckA, deckB;
    REP(i, n) { deck0.push_back(i); }
    REP(i, r) {
      int c; scanf("%d", &c);
      deckA.assign(deck0.begin() + n/2, deck0.end());
      deckB.assign(deck0.begin(), deck0.begin() + n/2);
      deck0.clear();
      while ((int)deck0.size() < n) {
        if (!deckA.empty()) {
          int m = min(c, (int)deckA.size());
          deck0.insert(deck0.end(), deckA.begin(), deckA.begin() + m);
          deckA.erase(deckA.begin(), deckA.begin() + m);
        }
        if (!deckB.empty()) {
          int m = min(c, (int)deckB.size());
          deck0.insert(deck0.end(), deckB.begin(), deckB.begin() + m);
          deckB.erase(deckB.begin(), deckB.begin() + m);
        }
      }
    }
    printf("%d\n", deck0.back());
  }
}
