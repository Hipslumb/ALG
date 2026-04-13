#pragma once
#include "Image.h"

void createImages(string filename, string outpath);
void testPixelationArtifacts(string filename);
float linearInterpolation(float x1, float y1, float x2, float y2, float x);
float bilinearInterpolation(
    float x1, float y1, float x2, float y2,
    float z11, float z12, float z21, float z22, float x, float y);

float linearSpline(const vector<float>& x, const vector<float>& y, float x_val);
vector<vector<float>> upsampleBlock(const vector<vector<float>>& small, int newH, int newW);

void FDCT(const vector<vector<double>>& s, vector<vector<double>>& S);
void IDCT(const vector<vector<double>>& S, vector<vector<double>>& s);

vector<vector<double>> DCTMatrix(int N);
vector<vector<double>> matrixMultiply(const vector<vector<double>>& A,
	const vector<vector<double>>& B);
vector<vector<double>> matrixTranspose(const vector<vector<double>>& A);
vector<vector<double>> DCT_bymatrix(const vector<vector<double>>& f, bool is_F);

vector<int> encodeDC(const vector<int>& dc);
vector<int> decodeDC(const vector<int>& diff);

struct AC {
    int run;
    int size;
    int code;
};

struct DC {
    int size;
    int code;
};

//Y
//vector<vector<int>> Y_q_Table() {
//    return {
//        {16, 11, 10, 16, 24, 40, 51, 61},
//        {12, 12, 14, 19, 26, 58, 60, 55},
//        {14, 13, 16, 24, 40, 57, 69, 56},
//        {14, 17, 22, 29, 51, 87, 80, 62},
//        {18, 22, 37, 56, 68, 109, 103, 77},
//        {24, 35, 55, 64, 81, 104, 113, 92},
//        {49, 64, 78, 87, 103, 121, 120, 101},
//        {72, 92, 95, 98, 112, 100, 103, 99}
//    };
//}
//
////Cb, Cr
//vector<vector<int>> CbCr_q_Table() {
//    return {
//        {17, 18, 24, 47, 99, 99, 99, 99},
//        {18, 21, 26, 66, 99, 99, 99, 99},
//        {24, 26, 56, 99, 99, 99, 99, 99},
//        {47, 66, 99, 99, 99, 99, 99, 99},
//        {99, 99, 99, 99, 99, 99, 99, 99},
//        {99, 99, 99, 99, 99, 99, 99, 99},
//        {99, 99, 99, 99, 99, 99, 99, 99},
//        {99, 99, 99, 99, 99, 99, 99, 99}
//    };
//}