#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <complex>
using namespace std;

#define LET(name, value) __typeof(value) name = value
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()
#define FOREACH(i, c) for (LET(i, (c).begin()); i != (c).end(); ++i)

const double EPS = 1e-10;
const double PI = 2*acos(0);
const double INF = 1e10;

typedef complex<double> P;
struct L { P pos, dir; };

inline int signum(double x) { return (abs(x) < EPS ? 0 : x > 0 ? 1 : -1); }
inline double inp(const P& a, const P& b) { return (conj(a)*b).real(); }
inline double outp(const P& a, const P& b) { return (conj(a)*b).imag(); }

inline int ccw(const P& p, const P& r, const P& s) {
  P a(r-p), b(s-p);
  int sgn = signum(outp(a, b));
  if (sgn != 0)
    return sgn;
  if (a.real()*b.real() < -EPS || a.imag()*b.imag() < -EPS)
    return -1;
  if (norm(a) < norm(b) - EPS)
    return 1;
  return 0;
}

bool ss_intersects(const L& s, const L& t) {
  return (ccw(s.pos, s.pos+s.dir, t.pos) *
      ccw(s.pos, s.pos+s.dir, t.pos+t.dir) <= 0 &&
      ccw(t.pos, t.pos+t.dir, s.pos) *
      ccw(t.pos, t.pos+t.dir, s.pos+s.dir) <= 0);
}

L segs[60];
double cost[60][60];

int main() {
  int n;
  while (scanf("%d", &n), n) {
    REP(i, n) REP(j, n) { cost[i][j] = INF; }
    REP(i, n) { cost[i][i] = 0; }
    REP(i, n) {
      double x1, y1, x2, y2;
      scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
      segs[i].pos = P(x1, y1);
      segs[i].dir = P(x2-x1, y2-y1);
    }
    double sx, sy, gx, gy;
    scanf("%lf%lf%lf%lf", &sx, &sy, &gx, &gy);
    P s(sx, sy), g(gx, gy);
    int start = 0, goal = 0;
    REP(i, n) {
      if (s == segs[i].pos || s == segs[i].pos + segs[i].dir) {
        start = i;
      } else if (g == segs[i].pos || g == segs[i].pos + segs[i].dir) {
        goal = i;
      }
    }

    REP(i, n) {
      FOR(j, i+1, n) {
        if (ss_intersects(segs[i], segs[j])) {
          double angle = fabs(arg(segs[i].dir) - arg(segs[j].dir));
          if (angle > PI) { angle = 2*PI - angle; }
          cost[i][j] = cost[j][i] = angle;
        }
      }
    }

    REP(i, n) REP(j, n) REP(k, n) {
      cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);
    }

    if (cost[start][goal] < INF) {
      printf("%f\n", 180 * cost[start][goal] / PI);
    } else {
      puts("-1");
    }
  }
}

