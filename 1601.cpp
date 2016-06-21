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

bool is_tanka(const vector<string>& words, int offset) {
    static const int TANKA[] = {5, 7, 5, 7, 7};

    int curr_idx = 0, curr_len = 0;
    FOR(i, offset, size(words)) {
        curr_len += size(words[i]);
        if (curr_len > TANKA[curr_idx])
            return false;
        if (curr_len == TANKA[curr_idx]) {
            curr_idx++;
            curr_len = 0;
            if (curr_idx == 5)
                return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int n;
    while (cin >> n, n) {
        vector<string> words(n);
        REP(i, n) cin >> words[i];

        REP(offset, n) {
            if (is_tanka(words, offset)) {
                cout << offset+1 << endl;
                break;
            }
        }
    }
}
