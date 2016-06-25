using Point = complex<double>;
namespace std { bool operator<(const Point& a, const Point& b) { return real(a) == real(b) ? imag(a) < imag(b) : real(a) < real(b); } }
double cross(const Point& a, const Point& b) { return imag(conj(a)*b); }
double dot(const Point& a, const Point& b) { return real(conj(a)*b); }

int ccw(Point a, Point b, Point c) {
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;
}

bool intersects(const Point& p1, const Point& p2, const Point& q1, const Point& q2) {
    return ccw(p1, p2, q1) * ccw(p1, p2, q2) <= 0 && ccw(q1, q2, p1) * ccw(q1, q2, p2) <= 0;
}

int contains(const vector<Point> polygon, const Point& p) {
    bool in = false;
    REP(i, polygon.size()) {
        Point a = polygon[i] - p;
        Point b = polygon[(i+1) % polygon.size()] - p;
        if (imag(a) > imag(b)) swap(a, b);
        if (imag(a) <= 0 && 0 < imag(b))
            if (cross(a, b) < 0)
                in = !in;
        if (cross(a, b) == 0 && dot(a, b) <= 0)
            return 1;   // on the edge
    }
    return in ? 2 : 0;
}

vector<Point> convex_hull(vector<Point>& points) {
    assert(points.size() >= 3);
    vector<Point> convex(points.size() * 2);
    sort(points.begin(), points.end());
    int k = 0;
    REP(i, points.size()) {
        while (k >= 2 && ccw(points[i], convex[k-1], convex[k-2]) >= 0) --k;
        convex[k++] = points[i];
    }
    int t = k+1;
    for (int i = points.size()-2; i >= 0; --i) {
        while (k >= t && ccw(points[i], convex[k-1], convex[k-2]) >= 0) --k;
        convex[k++] = points[i];
    }
    convex.resize(k-1);
    return convex;
}
