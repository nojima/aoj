#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int N;
    while (cin >> N, N) {
        static const complex<double> I = complex<double>(0, -1);
        using Point = complex<double>;
        vector<Point> points(N);
        REP(i, N) {
            double x, y; cin >> x >> y;
            points[i] = Point(x, y);
        }

        int ans = 1;
        REP(i, N) FOR(j, i+1, N) {
            auto x = points[i];
            auto y = points[j];
            double l_sq = norm(x - y);
            if (l_sq > 4) continue;
            for(double d : {-1, 1}) {
                Point middle = 0.5 * (x + y);
                Point dir = (x - y) * I;
                dir /= abs(dir);
                Point center = middle + d*sqrt(1 - l_sq/4)*dir;

                int count = 0;
                REP(k, N) {
                    if (norm(center - points[k]) <= 1 + 1e-10)
                        ++count;
                }
                ans = max(ans, count);
            }
        }
        cout << ans << '\n';
    }
}
