#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <complex>
using namespace std;

typedef complex<double> P;

struct ComplexLess {
  bool operator()(const P& lhs, const P& rhs) const {
    return (lhs.real() == rhs.real()) ? (lhs.imag() < rhs.imag()) : (lhs.real() < rhs.real());
  }
};

int main() {
  int m;
  while (cin >> m, m) {
    vector<P> asterism(m);
    for (int i = 0; i < m; ++i) {
      int x, y; cin >> x >> y;
      asterism[i] = P(x, y);
    }

    set<P, ComplexLess> stars;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
      int x, y; cin >> x >> y;
      stars.insert(P(x, y));
    }

    for (P p : stars) {
      P diff = p - asterism[0];
      auto pred = [&](P q){ return stars.count(q + diff); };
      if (all_of(asterism.begin(), asterism.end(), pred)) {
        cout << diff.real() << " " << diff.imag() << endl;
        break;
      }
    }
  }
}
