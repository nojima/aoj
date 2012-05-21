#include <cmath>
#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

const long double EPS = 1e-9;
typedef long long ll;
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define REPEQ(i, n) for (int i = 0; i <= (int)(n); ++i)
#define DOWN(i, n) for (int i = (n)-1; i >= 0; --i)
#define FOR(i, a, b) for (int i = (a); i < (int)(b); ++i)
#define FOREQ(i, a, b) for (int i = (a); i <= (int)(b); ++i)

struct Matrix {
  int n, m;
  long double** a;

  Matrix(int n, int m) { Create(n, m); }
  explicit Matrix(int n) { Create(1, n); }
  Matrix(const Matrix& mat) { Create(mat.n, mat.m); CopyFrom(mat); }
  virtual ~Matrix() { Release(); }

  void Create(int n, int m) {
    this->n = n; this->m = m;
    a = (long double**)calloc(n, sizeof(*a));
    REP(i, n) { a[i] = (long double*)calloc(m, sizeof(**a)); }
  }

  void Release() {
    REP(i, n) { free(a[i]); }
    free(a);
  }

  void CopyFrom(const Matrix& rhs) {
    assert(n == rhs.n && m == rhs.m);
    REP(i, n) REP(j, m) { a[i][j] = rhs[i][j]; }
  }

  void Swap(Matrix& rhs) {
    swap(n, rhs.n); swap(m, rhs.m); swap(a, rhs.a);
  }

  long double* operator[](int i) { return a[i]; }
  const long double* operator[](int i) const { return a[i]; }

  Matrix& operator+=(const Matrix& rhs) {
    assert(n == rhs.n && m == rhs.m);
    REP(i, n) REP(j, m) { a[i][j] += rhs[i][j]; }
    return *this;
  }

  const Matrix& operator+(const Matrix& rhs) const {
    return Matrix(*this) *= rhs;
  }

  Matrix& operator-=(const Matrix& rhs) {
    assert(n == rhs.n && m == rhs.m);
    REP(i, n) REP(j, m) { a[i][j] -= rhs[i][j]; }
  }

  const Matrix& operator-(const Matrix& rhs) const {
    return Matrix(*this) -= rhs;
  }

  Matrix& operator*=(const Matrix& rhs) {
    if (m == rhs.n) {   // matrix * matrix
      Matrix ret(n, rhs.m);
      REP(i, n) REP(j, rhs.m) REP(k, m) { ret[i][j] += a[i][k] * rhs[k][j]; }
      Swap(ret);
    } else if (rhs.n == 1 && m == rhs.m) {      // matrix * vector
      Matrix ret(1, n);
      REP(i, n) REP(k, m) { ret[0][i] += a[i][k] * rhs[0][k]; }
      Swap(ret);
    } else {
      assert(false);
    }
    return *this;
  }

  Matrix operator*(const Matrix& rhs) const {
    return Matrix(*this) *= rhs;
  }

  Matrix Pow(int k) const {
    assert(n == m);
    Matrix ret = Identity(n);
    Matrix temp = *this;
    while (k) {
      if (k & 1) { ret *= temp; }
      temp *= temp;
      k >>= 1;
    }
    return ret;
  }

  bool Solve(Matrix& vec) {
    assert(vec.n == 1 && n == m && n == vec.m);
    int pivot[n];
    long double* b = vec.a[0];
    REP(i, n) {
      pivot[i] = i;
      FOR(j, i+1, n) {
        if (fabs(a[j][i]) > fabs(a[pivot[i]][i])) { pivot[i] = j; }
      }
      swap(a[i], a[pivot[i]]);
      swap(b[i], b[pivot[i]]);
      if (fabs(a[i][i]) < EPS) { return false; }
      b[i] /= a[i][i];
      FOR(j, i+1, n) { a[i][j] /= a[i][i]; }
      FOR(j, i+1, n) { b[j] -= b[i] * a[j][i]; }
      FOR(j, i+1, n) FOR(k, i+1, n) { a[j][k] -= a[i][k] * a[j][i]; }
    }
    DOWN(i, n) REP(j, i) { b[j] -= a[j][i] * b[i]; }
    DOWN(i, n) { swap(b[i], b[pivot[i]]); }
    return true;
  }

  static Matrix Identity(int n) {
    Matrix ret(n, n);
    REP(i, n) { ret[i][i] = 1.0; }
    return ret;
  }
};

int S, N, K;
long double p[11][110];
long double E[110];

bool Near() {
  Matrix A = Matrix::Identity(N*K+1);
  FOREQ(x, 1, N*K) FOREQ(d, K, N*K) { A[x][abs(x - d)] -= p[K][d]; }
  Matrix b(N*K+1);
  FOREQ(i, 1, N*K) { b[0][i] = 1.0; }
  bool f = A.Solve(b);
  REPEQ(x, N*K) { E[x] = b[0][x]; }
  return f;
}

void Far() {
  if (S > N*K) {
    Matrix A(N*K+1, N*K+1);
    A[0][N*K] = A[N*K][N*K] = 1;
    REP(i, N*K) { A[0][i] = p[K][i+1]; }
    REP(i, N*K-1) { A[i+1][i] = 1; }
    Matrix b(N*K+1);
    b[0][N*K] = 1;
    REP(i, N*K) { b[0][i] = E[i+1]; }
    Matrix C = A.Pow(S-N*K);
    Matrix d = C * b;
    printf("%.12Lf\n", d[0][K-1]+EPS);
  } else {
    printf("%.12Lf\n", E[S]+EPS);
  }
}

int main() {
  scanf("%d%d%d", &S, &N, &K);
  S = abs(S);

  if (N == 1) {
    if (S % K == 0) { printf("%d\n", S / K); }
    else { puts("-1"); }
    return 0;
  }

  p[0][0] = 1;
  FOREQ(k, 1, K) FOREQ(d, 1, N*K) FOREQ(n, 1, N) {
    if (d >= n) { p[k][d] += p[k-1][d-n] / N; }
  }

  if (Near()) { Far(); }
  else { puts("-1"); }
}
