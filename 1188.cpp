#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <string>
#include <tuple>
using namespace std;

tuple<const char*, int> calc(const char* p)
{
    if (*p == '[') {
        vector<int> costs;
        const char* q = p + 1;
        while (*q != ']') {
            int c;
            tie(q, c) = calc(q);
            costs.push_back(c);
        }
        sort(begin(costs), end(costs));
        return make_tuple(q + 1, accumulate(begin(costs), begin(costs) + (costs.size() + 1) / 2, 0));
    } else {
        assert(isdigit(*p));
        int r = 0;
        for (; isdigit(*p); ++p) {
            r = r * 10 + *p - '0';
        }
        assert(*p == ']');
        return make_tuple(p, (r + 1) / 2);
    }
}

int main()
{
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        string line; cin >> line;
        const char* p;
        int r;
        tie(p, r) = calc(line.data());
        assert(p == line.data() + line.size());
        cout << r << endl;
    }
}
