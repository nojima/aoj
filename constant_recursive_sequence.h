// 定数係数の線形漸化式のn項目を求める。
// A[i] = coeff[0] + coeff[1]*A[i-1] + coeff[2]*A[i-2] + ... + coeff[k]*A[i-k]
// Arguments:
//   coeff: 係数の列。0番目の値は定数項。
//   init: 数列の初期値。A[0]からa[k-1]をこの順番で入れる。
//   n: 求める項
// Returns:
//   A[n] の値を返す。
// Verified: AOJ 2315 (Shadow Witch)
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
