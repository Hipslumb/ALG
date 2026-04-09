#include "fun.h"

vector<vector<vector<float>>> Image::splitBlocks() {
    vector<vector<vector<float>>> blocks;

    int blocksH = height / N;
    int blocksW = width / M;

    if (width % M != 0 || height % N != 0) {
        cout << "!!!!!Image size " << width << "x" << height
            << " not multiple of block size " << N << "x" << M << "\n";
    }

    for (int bi = 0; bi < blocksH; bi++) {
        for (int bj = 0; bj < blocksW; bj++) {
            vector<vector<float>> block(N, vector<float>(M));

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    int pj = bj * M + j;
                    int pi = bi * N + i;
                    int idx = pi * width + pj;

                    block[i][j] = (float)data[idx] - 128;
                }
            }

            blocks.push_back(block);
        }
    }
    return blocks;
}

vector<uc> Image::mergeBlocks(vector<vector<vector<float>>> blocks) {
    int blocksH = height / N;
    int blocksW = width / M;

    vector<uc> image(width * height);

    for (int bi = 0; bi < blocksH; bi++) {
        for (int bj = 0; bj < blocksW; bj++) {
            int blockIdx = bi * blocksW + bj;
            const auto& block = blocks[blockIdx];

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    int pj = bj * M + j;
                    int pi = bi * N + i;
                    int idx = pi * width + pj;

                    float val = block[i][j] + 128;
                    image[idx] = (uc)min(255.0f, max(0.0f, val));
                }
            }
        }
    }

    return image;
}

double C(int k) {
    if (k == 0) {
        return 1 / sqrt(2);
    }
    return 1.0;
}

void FDCT(const double s[N][M], double S[N][M]) {

    for (int u = 0; u < N; u++) {
        for (int v = 0; v < M; v++) {
            S[u][v] = 0;
        }
    }

    for (int u = 0; u < N; u++) {
        for (int v = 0; v < M; v++) {

            double sum = 0;

            for (int x = 0; x < N; x++) {
                for (int y = 0; y < M; y++) {
                    double cosX = cos((2 * x + 1) * u * acos(-1) / (2 * N));
                    double cosY = cos((2 * y + 1) * v * acos(-1) / (2 * M));

                    sum += s[x][y] * cosX * cosY;
                }
            }
            S[u][v] = (2 / sqrt(N * M)) * C(u) * C(v) * sum;
        }
    }
}

void IDCT(const double S[N][M], double s[N][M]) {

    for (int u = 0; u < N; u++) {
        for (int v = 0; v < M; v++) {
            s[u][v] = 0;
        }
    }

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {

            double sum = 0;

            for (int u = 0; u < N; u++) {
                for (int v = 0; v < M; v++) {
                    double cosX = cos((2 * x + 1) * u * acos(-1) / (2 * N));
                    double cosY = cos((2 * y + 1) * v * acos(-1) / (2 * M));

                    sum += S[x][y] * C(u) * C(v) * cosX * cosY;
                }
            }
            s[x][y] = (2 / sqrt(N * M)) * sum;
        }
    }
}

