#include <algorithm>
#include <cstdio>
using namespace std;

int R[8][1024];
int Rsize[8];
char str[2050];

inline int hex(char c) {
  if ('0' <= c && c <= '9') { return c - '0'; }
  else { return c - 'A' + 10; }
}

int gcd(int a, int b) {
  return b ? gcd(b, a%b) : a;
}

int lcm(int a, int b) {
  return a*b/gcd(a, b);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int N; scanf("%d ", &N);
    for (int i = 0; i < N; ++i) {
      fgets(str, sizeof(str), stdin);
      int j, g = 0;
      for (j = 0; str[j] && str[j] != '\n'; j += 2) {
        R[i][j/2] = hex(str[j])*16 + hex(str[j+1]);
        if (R[i][j/2] != 0) { g = gcd(g, j/2); }
      }
      Rsize[i] = j/2;
      if (g > 1) {
        for (int k = 0; k < Rsize[i]; k += g) {
          R[i][k/g] = R[i][k];
        }
        Rsize[i] /= g;
      }
      printf("%d ", Rsize[i]);
    }
    puts("");

    int l = 1;
    for (int i = 0; i < N; ++i) { l = lcm(l, Rsize[i]); }

    if (l > 1024) {
      puts("Too complex.");
    } else {
      printf("%d\n", l);
    }
  }
}
