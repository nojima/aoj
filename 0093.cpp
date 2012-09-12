#include <iostream>
using namespace std;

int main() {
  int a, b;
  for (int T = 0; cin >> a >> b, a | b; ++T) {
    if (T > 0) { cout << endl; }
    bool exist = false;
    for (int y = a; y <= b; ++y) {
      if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)) {
        cout << y << endl;
        exist = true;
      }
    }
    if (!exist) { cout << "NA" << endl; }
  }
}
