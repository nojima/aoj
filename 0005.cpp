#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  long long a, b;
  while (cin >> a >> b) {
    long long g = __gcd(a, b);
    cout << g << " " << a * b / g << endl;
  }
}
