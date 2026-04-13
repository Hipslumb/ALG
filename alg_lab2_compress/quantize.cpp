#include "fun.h"

vector<vector<int>> quantize(const vector<vector<double>>& dct,
    const vector<vector<int>>& q_table) {
    int N = dct.size();
    int M = dct[0].size();

    vector<vector<int>> quantized(N, vector<int>(M, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            double val = dct[i][j] / q_table[i][j];
            quantized[i][j] = (int)round(val);
        }
    }

    return quantized;
}

vector<vector<double>> dequantize(const vector<vector<int>>& quantized,
    const vector<vector<int>>& q_table) {
    int N = quantized.size();
    int M = quantized[0].size();

    vector<vector<double>> dct(N, vector<double>(M, 0.0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dct[i][j] = quantized[i][j] * q_table[i][j];
        }
    }

    return dct;
}