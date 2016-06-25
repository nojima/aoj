#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i=0;i<int(n);++i)
#define FOR(i, a, b) for(int i=int(a);i<int(b);++i)

typedef pair<int, int> Point;
typedef vector<Point> Line;

void normalize1(Line& line) {
    int offset_x = line[0].first;
    int offset_y = line[0].second;
    for (auto& p : line) {
        p.first -= offset_x;
        p.second -= offset_y;
    }

    while (line[1].first <= 0 || line[1].second != 0) {
        for (auto& p : line) {
            p = make_pair(-p.second, p.first);
        }
    }
}

void normalize2(Line& line) {
    Line reversed(line);
    normalize1(line);
    reverse(reversed.begin(), reversed.end());
    normalize1(reversed);
    if (reversed < line)
        line = reversed;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int n;
    while (cin >> n, n) {
        vector<Line> lines(n+1);

        REP(i, n+1) {
            int m; cin >> m;
            lines[i].resize(m);
            REP(j, m) {
                cin >> lines[i][j].first >> lines[i][j].second;
            }
            normalize2(lines[i]);
        }

        FOR(i, 1, n+1) {
            if (lines[i] == lines[0])
                cout << i << '\n';
        }

        cout << "+++++\n";
    }
}
