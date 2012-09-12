#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  long long d = 100000;
  for (int i = 0; i < n; ++i) {
    d *= 1.05;
    if (d % 1000) { d += 1000 - d % 1000; }
  }
  cout << d << endl;
}
