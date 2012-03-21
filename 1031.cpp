#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

struct Panel {
  char name[1024];
  int x1, y1, x2, y2;
  vector<Panel*> children;
};

pair<Panel*, const char*> parse(const char* input) {
  Panel* panel = new Panel;
  sscanf(input, "<%[^>]>%d,%d,%d,%d",
      panel->name, &panel->x1, &panel->y1, &panel->x2, &panel->y2);
  input = strchr(input+1, '<');
  while (input[1] != '/') {
    pair<Panel*, const char*> p = parse(input);
    panel->children.push_back(p.first);
    input = p.second;
  }
  return make_pair(panel, strchr(input, '>')+1);
}

inline bool point_in_rect(int x, int y, int x1, int y1, int x2, int y2) {
  return x1 <= x && x <= x2 && y1 <= y && y <= y2;
}

void dfs(Panel* panel, int x, int y) {
  bool b = true;
  FOREACH(it, panel->children) {
    Panel* child = *it;
    if (point_in_rect(x, y, child->x1, child->y1, child->x2, child->y2)) {
      dfs(child, x, y);
      b = false;
    }
  }
  if (b) { printf("%s %zd\n", panel->name, panel->children.size()); }
}

int main() {
  int n;
  while (scanf("%d", &n), n) {
    char input[1024]; scanf("%s", input);
    pair<Panel*, const char*> p = parse(input);
    Panel* root = p.first;
    assert(*p.second == 0);
    REP(i, n) {
      int x, y; scanf("%d%d", &x, &y);
      if (point_in_rect(x, y, root->x1, root->y1, root->x2, root->y2)) {
        dfs(root, x, y);
      } else {
        puts("OUT OF MAIN PANEL 1");
      }
    }
  }
}
