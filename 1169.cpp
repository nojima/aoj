#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

struct Edge {
  int src;
  string label;

  Edge(int src, const char* label): src(src), label(label) {}
};

const int MAX_VERTEX_COUNT = 40;
const int MAX_SPELL_LEN = 2*6*40+1;

vector<Edge> edges[MAX_VERTEX_COUNT];
string dp[MAX_SPELL_LEN+1][MAX_VERTEX_COUNT];

int main() {
  int n, a, s, g;
  while (scanf("%d%d%d%d", &n, &a, &s, &g), n|a|s|g) {
    REP(v, n) { edges[v].clear(); }

    REP(i, a) {
      int x, y;
      char label[10];
      scanf("%d%d%s", &x, &y, label);
      edges[y].push_back(Edge(x, label));
    }

    REP(v, n) {
      dp[0][v] = (v == s) ? "" : "~";
    }

    int max_spell_len = 2*6*n+1;
    FOREQ(l, 1, max_spell_len) {
      REP(v, n) {
        string val = "~";
        FOREACH(it, edges[v]) {
          int u = it->src;
          const string& label = it->label;
          if ((int)label.size() > l) { continue; }
          const string& spell = dp[l - label.size()][u];
          if (spell == "~") { continue; }
          val = min(val, spell + label);
        }
        dp[l][v] = val;
      }
    }

    string ans = "~";
    FOREQ(l, 0, max_spell_len) {
      ans = min(ans, dp[l][g]);
    }
    if (ans != "~" && (int)ans.size() < max_spell_len / 2) {
      puts(ans.c_str());
    } else {
      puts("NO");
    }
  }
}
