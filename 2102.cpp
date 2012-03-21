#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    pair<int, char> card[9];
    for (int i = 0; i < 9; ++i) { scanf("%d", &card[i].first); }
    for (int i = 0; i < 9; ++i) { scanf(" %c", &card[i].second); }
    int ans = 0;
    sort(card, card+9);
    do {
      for (int i = 0; i < 3; ++i) {
        for (int j = 1; j < 3; ++j) {
          if (card[3*i+j].second != card[3*i].second) { goto bad; }
        }
        bool same = true;
        for (int j = 1; j < 3; ++j) {
          if (card[3*i+j].first != card[3*i].first) {
            same = false;
            break;
          }
        }
        bool renban = true;
        for (int j = 1; j < 3; ++j) {
          if (card[3*i+j].first != card[3*i+j-1].first + 1) {
            renban = false;
            break;
          }
        }
        if (!same && !renban) { goto bad; }
      }
      ans = 1;
      break;
bad:;
    } while (next_permutation(card, card+9));
    printf("%d\n", ans);
  }
}

