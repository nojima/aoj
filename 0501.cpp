#include <cstdio>
#include <map>
using namespace std;

int main() {
  int n;
  while (scanf("%d", &n), n) {
    map<char, char> table;
    for (int i = 0; i < n; ++i) {
      char from, to; scanf(" %c %c", &from, &to);
      table[from] = to;
    }
    int m; scanf("%d", &m);
    for (int i = 0; i < m; ++i){
      char ch; scanf(" %c", &ch);
      putchar(table.count(ch) ? table[ch] : ch);
    }
    puts("");
  }
}

