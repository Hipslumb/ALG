#include "fun.h"

vector<vector<int>> quantize(const vector<vector<double>>& dct, const int q_table[64]) {
    int N = dct.size();
    int M = dct[0].size();

    vector<vector<int>> quantized(N, vector<int>(M, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            double val = dct[i][j] / q_table[i * 8 + j];
            quantized[i][j] = (int)round(val);
        }
    }

    return quantized;
}

vector<vector<double>> dequantize(const vector<vector<int>>& quantized, const int q_table[64]) {
    int N = quantized.size();
    int M = quantized[0].size();

    vector<vector<double>> dct(N, vector<double>(M, 0.0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dct[i][j] = quantized[i][j] * q_table[i * 8 + j];
        }
    }

    return dct;
}

map<string, int> reverse(const map<int, string>& table) {
    map<string, int> reversed;
    for (auto& p : table) {
        reversed[p.second] = p.first;
    }
    return reversed;
}

void new_table(const int baseQ[64], int quality, int outQ[64]) {
    if (quality < 1) quality = 1;
    if (quality > 100) quality = 100;

    double S;
    if (quality < 50) {
        S = 5000.0 / quality;
    }
    else {
        S = 200.0 - 2.0 * quality;
    }

    for (int i = 0; i < 64; i++) {
        double val = (baseQ[i] * S) / 100.0;
        outQ[i] = max(1, (int)round(val));
    }
}
