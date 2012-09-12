#include <cstdio>
#include <cmath>
using namespace std;

int main() {
  double a, b, c, d, e, f;
  while (scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f) != EOF) {
    double det = a * e - b * d;
    double x = (c * e - b * f) / det;
    double y = (a * f - c * d) / det;
    if (fabs(x) < 1e-8) { x = 0; }
    if (fabs(y) < 1e-8) { y = 0; }
    printf("%.3f %.3f\n", x, y);
  }
}
