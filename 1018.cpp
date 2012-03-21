#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

int array[100];

int main() {
  int n;
  while (scanf("%d", &n) != EOF) {
    REP(i, n) { scanf("%d", array+i); }
    sort(array, array+n);
    int ans = 0, sum = 0;
    REP(i, n) { sum += array[i]; ans += sum; }
    printf("%d\n", ans);
  }
}
