#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>
using namespace std;

static const double eps = 1e-10;
typedef complex<double> point;
struct circle { point p; double r; };
inline double sq(double x) { return x * x; }

pair<point, point> cross(const circle& c1, const circle& c2)
{
    double d = abs(c1.p - c2.p);
    double rc = (sq(d) + sq(c1.r) - sq(c2.r)) / (2*d);
    double rs = sqrt(sq(c1.r) - sq(rc));
    point diff = (c2.p - c1.p) / d;
    return make_pair(c1.p + diff * point(rc, rs),
                     c1.p + diff * point(rc, -rs));
}

bool check_point(const vector<circle>& circles, point p)
{
    return all_of(begin(circles), end(circles),
            [p](const circle& c){ return sq(c.r + eps) > norm(c.p - p); });
}

bool check(const vector<circle>& ropes, double h)
{
    vector<circle> circles;
    for (const auto& c : ropes) {
        double r = sqrt(sq(c.r) - sq(h));
        circles.push_back({ c.p, r });
    }

    for (int i = 0; i < (int)circles.size(); ++i) {
        const circle& c1 = circles[i];
        if (check_point(circles, c1.p))
            return true;

        for (int j = i + 1; j < (int)circles.size(); ++j) {
            const circle& c2 = circles[j];
            double sqd = norm(c1.p - c2.p);
            if (sq(c1.r + c2.r) <= sqd)
                return false;
            auto cp = cross(c1, c2);
            if (check_point(circles, cp.first))
                return true;
            if (check_point(circles, cp.second))
                return true;
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n) {
        double lo = 0, hi = 1e10;
        vector<circle> ropes;

        for (int i = 0; i < n; ++i) {
            double x, y, r;
            cin >> x >> y >> r;
            ropes.push_back({ point(x, y), r });
            hi = min(hi, r);
        }

        for (int i = 0; i < 100; ++i) {
            double mid = (lo + hi) / 2;
            if (check(ropes, mid))
                lo = mid;
            else
                hi = mid;
        }

        cout.precision(15);
        cout << hi << endl;
    }
}
