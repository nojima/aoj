#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define REPEQ(i, n) FOREQ(i, 0, n)
#define ALL(c) (c).begin(), (c).end()

template <typename T> inline int size(const T& x) { return x.size(); }

pair<int, int> calculate(const vector<string>& lines, int index, int level) {
    if (level >= size(lines[index]))
        return make_pair(-1, index);

    char ch = lines[index][level];
    if ('0' <= ch && ch <= '9')
        return make_pair(ch - '0', index+1);

    assert(ch == '+' || ch == '*');

    int ret_value = (ch == '+') ? 0 : 1;
    int ret_index = index+1;
    for (;;) {
        auto x = calculate(lines, ret_index, level+1);
        if (x.first == -1)
            break;
        ret_value = (ch == '+') ? (ret_value + x.first) : (ret_value * x.first);
        ret_index = x.second;
    }
    return make_pair(ret_value, ret_index);
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int n;
    while (cin >> n, n) {
        vector<string> lines(n+1);
        REP(i, n) cin >> lines[i];

        cout << calculate(lines, 0, 0).first << endl;
    }
}
