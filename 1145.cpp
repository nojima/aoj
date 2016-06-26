#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

struct Result {
    long long length;
    int index;
};

Result expand2(const string& s, int i, int target);

Result expand1(const string& s, int i, int target) {
    if (isalpha(s[i])) {
        int start = i, length = 0;
        for (; isalpha(s[i]); ++i) ++length;
        if (target < length)
            throw s[start + target];
        return (Result){length, i};
    }
    if (isdigit(s[i])) {
        int n_repeat = 0;
        for (; isdigit(s[i]); ++i)
            n_repeat = 10*n_repeat + (s[i]-'0');
        if (s[i] == '(') {
            Result r = expand2(s, i+1, target);
            assert(s[r.index] == ')');
            if (n_repeat * r.length > target) {
                expand2(s, i+1, target % r.length);
                assert(false);
            }
            return (Result){n_repeat * r.length, r.index + 1};
        }
        if (isalpha(s[i])) {
            if (target < n_repeat)
                throw s[i];
            return (Result){n_repeat, i + 1};
        }
        assert(false);
    }
    assert(false);
}

Result expand2(const string& s, int i, int target) {
    long long length = 0;
    for (;;) {
        Result r = expand1(s, i, target);
        length += r.length;
        target -= r.length;
        i = r.index;
        if (s[i] == '\0' || s[i] == ')')
            return (Result){length, i};
    }
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    string s; int i;
    while (cin>>s>>i, s!="0"||i!=0) {
        s += '\0';
        try {
            expand2(s, 0, i);
            cout << "0\n";
        } catch (char ch) {
            cout << ch << '\n';
        }
    }
}
