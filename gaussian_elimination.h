// ガウスの消去法で以下の形のn変数連立一次方程式の解を求める。
//   m[0][0]*x[0]   + m[0][1]*x[1]   + ... + m[n-1][0]*x[n-1]   = m[0][n]
//   m[1][0]*x[0]   + m[1][1]*x[1]   + ... + m[n-1][1]*x[n-1]   = m[1][n]
//   ...
//   m[n-1][0]*x[0] + m[n-1][1]*x[1] + ... + m[n-1][n-1]*x[n-1] = m[n-1][n]
// Arguments:
//   matrix: (n, n+1)-行列。上の説明のmに相当する。
// Returns:
//   解となるn次ベクトル。解が複数あったり存在しない場合は空のvectorを返す。
// Verified:
//   AOJ 2315 (Shadow Witch)
vector<double> gaussian_elimination(vector<vector<double>> matrix) {
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
