#include <algorithm>
#include <iostream>
using namespace std;

template <class T> inline int size(const T& x) { return x.size(); }

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  int n, k;
  while (cin >> n >> k, n | k) {
    vector<int> cards(k);
    for (int i = 0; i < k; ++i)
      cin >> cards[i];
    sort(cards.begin(), cards.end());

    bool hakushi = false;
    if (cards[0] == 0) {
      hakushi = true;
      cards.erase(cards.begin());
    }

    int ans = 0, prev = -1000, prevLength = 0;
    for (int i = 0; i < size(cards); ) {
      int head = i;
      for (++i; i < size(cards); ++i) {
        if (cards[i] != cards[i-1] + 1)
          break;
      }
      int tail = i - 1;
      int length = tail - head + 1;
      if (hakushi && prev + 2 == cards[head])
        ans = max(ans, prevLength + 1 + length);
      else if (hakushi && (1 < cards[head] || cards[tail] < k))
        ans = max(ans, length + 1);
      else
        ans = max(ans, length);
      prev = cards[tail];
      prevLength = length;
    }

    cout << ans << endl;
  }
}
