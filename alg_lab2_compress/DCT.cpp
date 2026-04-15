#include "fun.h"

vector<vector<vector<double>>> split_blocks(const vector<uc>& channel, int w, int h, int N, int M) {
    vector<vector<vector<double>>> blocks;

    int blocksW = w / M;
    int blocksH = h / N;

    for (int bi = 0; bi < blocksH; bi++) {
        for (int bj = 0; bj < blocksW; bj++) {
            vector<vector<double>> block(N, vector<double>(M));

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    int px = bj * M + j;
                    int py = bi * N + i;
                    block[i][j] = (double)channel[py * w + px] - 128.0;
                }
            }
            blocks.push_back(block);
        }
    }
    return blocks;
}

vector<uc> merge_blocks(const vector<vector<vector<double>>>& blocks, int w, int h, int N, int M) {
    int blocksW = w / M;
    int blocksH = h / N;

    vector<uc> channel(w * h);

    for (int bi = 0; bi < blocksH; bi++) {
        for (int bj = 0; bj < blocksW; bj++) {
            int idx = bi * blocksW + bj;
            vector<vector<double>> block = blocks[idx];

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    int px = bj * M + j;
                    int py = bi * N + i;
                    double val = block[i][j] + 128.0;
                    channel[py * w + px] = (uc)min(255.0, max(0.0, val));
                }
            }
        }
    }
    return channel;
}

double C(int k) {
    if (k == 0) {
        return 1.0 / sqrt(2.0);
    }
    return 1.0;
}

void FDCT(const vector<vector<double>>& s, vector<vector<double>>& S) {

    int n = s.size();
    int m = s[0].size();

    S.assign(n, vector<double>(m, 0.0f));

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < m; v++) {

            double sum = 0;

            for (int x = 0; x < n; x++) {
                for (int y = 0; y < m; y++) {
                    double cosX = cos((2.0 * x + 1.0) * u * acos(-1) / (2.0 * n));
                    double cosY = cos((2.0 * y + 1.0) * v * acos(-1) / (2.0 * m));

                    sum += s[x][y] * cosX * cosY;
                }
            }
            S[u][v] = (2.0 / sqrt(n * m)) * C(u) * C(v) * sum;
        }
    }
}

void IDCT(const vector<vector<double>>& S, vector<vector<double>>& s) {

    int n = S.size();
    int m = S[0].size();

    s.assign(n, vector<double>(m, 0.0f));

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {

            double sum = 0;

            for (int u = 0; u < n; u++) {
                for (int v = 0; v < m; v++) {
                    double cosX = cos((2.0 * x + 1.0) * u * acos(-1) / (2.0 * n));
                    double cosY = cos((2.0 * y + 1.0) * v * acos(-1) / (2.0 * m));

                    sum += S[u][v] * C(u) * C(v) * cosX * cosY;
                }
            }
            s[x][y] = (2.0 / sqrt(n * m)) * sum;
        }
    }
}

vector<uc> useDCT(const vector<uc>& channel, int w, int h, int N, int M, bool is_F) {
    vector<vector<vector<double>>> blocks = split_blocks(channel, w, h, N, M);

    for (auto& block : blocks) {

        /*if (is_F) FDCT(block, dctBlock);
        else  IDCT(block, dctBlock);
        block = dctBlock;*/

        block = DCT_bymatrix(block, is_F);
    }

    return merge_blocks(blocks, w, h, N, M);
}
//MATRIX

vector<vector<double>> DCTMatrix(int N) {
    vector<vector<double>> A(N, vector<double>(N, 0.0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double Cos = cos((2.0 * j + 1.0) * i * acos(-1) / (2.0 * N));
            A[i][j] = C(i) * sqrt(2.0 / N) * Cos;
        }
    }
    return A;
}

//A * B
vector<vector<double>> matrixMultiply(const vector<vector<double>>& A,
    const vector<vector<double>>& B) {
    int n = A.size();
    int m = B[0].size();
    int p = A[0].size();

    vector<vector<double>> C(n, vector<double>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            double sum = 0;
            for (int k = 0; k < p; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    return C;
}

vector<vector<double>> matrixTranspose(const vector<vector<double>>& A) {
    int n = A.size();
    int m = A[0].size();

    vector<vector<double>> AT(m, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            AT[j][i] = A[i][j];
        }
    }

    return AT;
}

vector<vector<double>> DCT_bymatrix(const vector<vector<double>>& f, bool is_F) {
    int N = f.size();
    int M = f[0].size();

    auto A = DCTMatrix(N);
    auto B = DCTMatrix(M);
    if (is_F) {
        // F = A * f * B^T
        auto BT = matrixTranspose(B);
        auto temp = matrixMultiply(A, f);
        auto F = matrixMultiply(temp, BT);
        return F;
    }
    else {
        // f = A^T * F * B
        auto AT = matrixTranspose(A);
        auto temp = matrixMultiply(AT, f);
        auto f = matrixMultiply(temp, B);
        return f;
    }
}
