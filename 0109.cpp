#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

pair<ll, const char*> expr(const char*);
pair<ll, const char*> term(const char*);
pair<ll, const char*> fact(const char*);

pair<ll, const char*> expr(const char* p) {
  pair<ll, const char*> lhs = term(p);
  ll ret = lhs.first;
  const char* q = lhs.second;
  while (*q == '+' || *q == '-') {
    pair<ll, const char*> rhs = term(q + 1);
    if (*q == '+') { ret += rhs.first; }
    else { ret -= rhs.first; }
    q = rhs.second;
  }
  return make_pair(ret, q);
}

pair<ll, const char*> term(const char* p) {
  pair<ll, const char*> lhs = fact(p);
  ll ret = lhs.first;
  const char* q = lhs.second;
  while (*q == '*' || *q == '/') {
    pair<ll, const char*> rhs = fact(q + 1);
    if (*q == '*') { ret *= rhs.first; }
    else { ret /= rhs.first; }
    q = rhs.second;
  }
  return make_pair(ret, q);
}

pair<ll, const char*> fact(const char* p) {
  if (*p == '(') {
    pair<ll, const char*> inside = expr(p + 1);
    return make_pair(inside.first, inside.second + 1);
  } else {
    ll ret = 0;
    const char* q;
    for (q = p; '0' <= *q && *q <= '9'; ++q) {
      ret *= 10;
      ret += *q - '0';
    }
    return make_pair(ret, q);
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    char buffer[128]; scanf("%s", buffer);
    pair<ll, const char*> ret = expr(buffer);
    printf("%lld\n", ret.first);
  }
}
