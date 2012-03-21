#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

bool match(const string& str, const string& pat) {
  if (str.size() != pat.size()) { return false; }
  REP(i, str.size()) {
    if (pat[i] == '?') { continue; }
    if (str[i] != pat[i]) { return false; }
  }
  return true;
}

int main() {
  int n, m;
  while (cin >> n >> m, n|m) {
    vector<bool> permits(n);
    vector<string> srcs(n);
    vector<string> dsts(n);
    string keyword;
    REP(i, n) {
      cin >> keyword >> srcs[i]>> dsts[i];
      permits[i] = (keyword == "permit");
    }

    string src, dst, msg;
    vector<string> ans;
    REP(j, m) {
      cin >> src >> dst >> msg;
      bool ok = false;
      REP(i, n) {
        if (match(src, srcs[i]) && match(dst, dsts[i])) {
          ok = permits[i];
        }
      }
      if (ok) {
        ans.push_back(src + " " + dst + " " + msg);
      }
    }

    cout << ans.size() << endl;
    FOREACH(it, ans) { cout << *it << endl; }
  }
}

