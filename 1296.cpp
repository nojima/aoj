#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <queue>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

bool gsub(char* out, const char* str, const char* pat, const char* rep)
{
  bool ret = false;
  int n = strlen(pat), m = strlen(rep);
  const char *cur, *prev = str;
  for (;; ret = true) {
    cur = strstr(prev, pat);
    if (cur == NULL) { break; }
    memcpy(out, prev, cur - prev);
    out += cur - prev;
    memcpy(out, rep, m);
    out += m;
    prev = cur + n;
  }
  strcpy(out, prev);
  return ret;
}

struct Entry {
  char str[101];
  int cost;
};

char pat[10][11], rep[10][11];
char gamma[11], delta[11];

int main() {
  int n;
  while (scanf("%d", &n), n) {
    REP(i, n) {
      scanf("%s%s", pat[i], rep[i]);
    }
    scanf("%s%s", gamma, delta);
    size_t m = strlen(delta);
    queue<Entry> Q;
    Entry s;
    s.cost = 0;
    strcpy(s.str, gamma);
    Q.push(s);
    while (!Q.empty()) {
      Entry e = Q.front(); Q.pop();
      if (strcmp(e.str, delta) == 0) {
        printf("%d\n", e.cost);
        goto next;
      }
      REP(i, n) {
        Entry f;
        f.cost = e.cost + 1;
        if (gsub(f.str, e.str, pat[i], rep[i]) && strlen(f.str) <= m) {
          Q.push(f);
        }
      }
    }
    puts("-1");
next:;
  }
}
