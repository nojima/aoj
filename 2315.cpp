#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)

vector<vector<double>> matrix_product(const vector<vector<double>>& a, const vector<vector<double>>& b) {
    int ra = a.size(), ca = a[0].size(), rb = b.size(), cb = b[0].size();
    assert(ca == rb);
    vector<vector<double>> matrix(ra, vector<double>(cb));
    REP(r, ra) REP(c, cb) REP(k, ca)
        matrix[r][c] += a[r][k] * b[k][c];
    return matrix;
}

vector<double> matrix_vector_product(const vector<vector<double>>& a, const vector<double>& b) {
    int nr = a.size(), nc = a[0].size();
    assert(nc == (int)b.size());
    vector<double> result(nr);
    REP(r, nr) REP(k, nc) result[r] += a[r][k] * b[k];
    return result;
}

vector<vector<double>> matrix_power(vector<vector<double>> matrix, unsigned k) {
    int n = matrix.size();
    vector<vector<double>> result(n, vector<double>(n));
    REP(i, n) result[i][i] = 1;
    for (; k; k >>= 1) {
        if (k & 1)
            result = matrix_product(result, matrix);
        matrix = matrix_product(matrix, matrix);
    }
    return result;
}

// 以下の形の定数係数線形漸化式のn項目を求める。
//   A[i] = coeff[0] + coeff[1]*A[i-1] + coeff[2]*A[i-2] + ... + coeff[k]*A[i-k]
// Arguments:
//   coeff: 係数の列。0番目の値は定数項。
//   init: 数列の初期値。A[0]からa[k-1]をこの順番で入れる。
//   n: 求める項
// Returns:
//   A[n] の値を返す。
double constat_recursive_sequence(const vector<double>& coeff, const vector<double>& init, int n) {
    int k = coeff.size()-1;
    vector<vector<double>> matrix(k+1, vector<double>(k+1));
    matrix[0][k] = matrix[k][k] = coeff[0];
    REP(i, k) matrix[0][i] = coeff[i+1];
    REP(i, k-1) matrix[i+1][i] = 1;
    matrix = matrix_power(matrix, n-k+1);
    vector<double> v0(k+1);
    v0[k] = 1;
    REP(i, k) v0[i] = init[k-i-1];
    return matrix_vector_product(matrix, v0)[0];
}

// ガウスの消去法で連立一次方程式の解を求める。
// Arguments:
//   matrix: (n, n+1)-行列。この関数はこの行列を破壊的に変更する。
// Returns:
//   vector<double>: 解となるベクトル。解が複数あったり存在しない場合は空のvectorを返す。
vector<double> gaussian_elimination(vector<vector<double>>& matrix) {
    static const double eps = 1e-10;
    int n = matrix.size();
    assert((int)matrix[0].size() == n+1);
    vector<int> column(n);
    REP(i, n) column[i] = i;

    // forward
    REP(i, n) {
        // pivot
        int pivot_r = i, pivot_c = i;
        FOR(r, i, n) FOR(c, i, n)
            if (abs(matrix[r][c]) > abs(matrix[pivot_r][pivot_c]))
                pivot_r = r, pivot_c = c;
        swap(matrix[pivot_r], matrix[i]);
        swap(column[pivot_c], column[i]);
        REP(r, n) swap(matrix[r][pivot_c], matrix[r][i]);
        if (abs(matrix[i][i]) < eps)
            return vector<double>();    // no solutions or many solutions
        // reduction
        double t = 1.0 / matrix[i][i];
        FOR(c, i, n+1) matrix[i][c] *= t;
        FOR(r, i+1, n) {
            double s = matrix[r][i];
            FOR(c, i, n+1) matrix[r][c] -= s * matrix[i][c];
        }
    }

    // backward
    vector<double> answer(n);
    for (int i = n-1; i >= 0; --i) {
        REP(r, i) matrix[r][n] -= matrix[r][i] * matrix[i][n];
        answer[column[i]] = matrix[i][n];
    }
    return answer;
}

void print_float(double x, int precision=10) {
    cout.setf(ios::fixed);
    cout.precision(precision);
    cout << x << '\n';
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int S, N, K;
    while (cin >> S >> N >> K) {
        int L = N*K;
        vector<vector<double>> prob(K+1, vector<double>(L+1));
        FOR(v, 1, N+1) prob[1][v] = 1.0 / N;
        FOR(k, 2, K+1) REP(v, L+1) {
            FOR(i, 1, N+1) if (v-i > 0)
                prob[k][v] += prob[k-1][v-i] / N;
        }
        S = abs(S);

        if (N == 1) {
            if (S % K == 0)
                cout << S/K << endl;
            else
                cout << -1 << endl;
            continue;
        }

        vector<vector<double>> matrix(L+1, vector<double>(L+2));
        matrix[0][0] = -1;
        FOR(p, 1, L+1) {
            matrix[p][p] = -1;
            matrix[p][L+1] = -1;
            FOR(i, 1, L+1) matrix[p][abs(p-i)] += prob[K][i];
        }
        vector<double> solution = gaussian_elimination(matrix);
        assert(!solution.empty());
        if (S <= L) {
            print_float(solution[S]);
        } else {
            vector<double> coeff(L+1);
            coeff[0] = 1;
            REP(i, L) coeff[i+1] = prob[K][i+1];
            print_float(constat_recursive_sequence(coeff, solution, S));
        }
    }
}
