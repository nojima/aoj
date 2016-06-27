// Verified: AOJ 2315 (Shadow Witch)

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
