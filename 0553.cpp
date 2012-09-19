#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(false);

  ll N, maxHp;
  while (cin >> N >> maxHp) {
    vector<ll> totalDamage(N);
    ll totalHealing = 0, answer = 0;
    priority_queue<pair<ll, int>> Q;
    int maxIndex = 0;

    for (int i = 0; i < N - 1; ++i) {
      ll damage, healing;
      cin >> damage >> healing;
      totalDamage[i + 1] = totalDamage[i] + damage;
      Q.push({healing, i});

      ll necessaryHealing = totalDamage[i + 1] - totalHealing - maxHp + 1;
      while (necessaryHealing > 0) {
        ll healing = Q.top().first;
        int index = Q.top().second;
        Q.pop();

        if (index < maxIndex) continue;
        maxIndex = index;

        ll netDamage = totalDamage[index] - totalHealing;
        ll times = min((necessaryHealing + healing - 1) / healing, netDamage / healing);
        answer += times;
        necessaryHealing -= healing * times;
        netDamage -= healing * times;
        totalHealing += healing * times;
        if (netDamage > 0) Q.push({min(healing, netDamage), index});
      }
    }
    cout << answer << endl;
  }
}
