#pragma once
#include "Image.h"

void createImages(string filename, string outpath);
void testPixelationArtifacts(string filename);
float linearInterpolation(float x1, float y1, float x2, float y2, float x);
float bilinearInterpolation(
    float x1, float y1, float x2, float y2,
    float z11, float z12, float z21, float z22, float x, float y);

float linearSpline(const vector<float>& x, const vector<float>& y, float x_val);

vector<uc> downsampling(const vector<uc>& channel, int w, int h, int k);
vector<uc> upsampling(const vector<uc>& channel, int w, int h, int k);
vector<vector<float>> upsampleBlock(const vector<vector<float>>& small, int newH, int newW);
vector<uc> resize(const vector<uc>& channel, int oldW, int oldH, int newW, int newH);

vector<vector<vector<double>>> split_blocks(const vector<uc>& channel, int w, int h, int N, int M);
vector<uc> merge_blocks(const vector<vector<vector<double>>>& blocks, int w, int h, int N, int M);
void FDCT(const vector<vector<double>>& s, vector<vector<double>>& S);
void IDCT(const vector<vector<double>>& S, vector<vector<double>>& s);

vector<vector<double>> DCTMatrix(int N);
vector<vector<double>> matrixMultiply(const vector<vector<double>>& A,
	const vector<vector<double>>& B);
vector<vector<double>> matrixTranspose(const vector<vector<double>>& A);
vector<vector<double>> DCT_bymatrix(const vector<vector<double>>& f, bool is_F);
vector<uc> useDCT(const vector<uc>& channel, int w, int h, int N, int M, bool is_F);

vector<vector<int>> quantize(const vector<vector<double>>& dct, const int q_table[64]);
vector<vector<double>> dequantize(const vector<vector<int>>& quantized, const int q_table[64]);
void new_table(const int baseQ[64], int quality, int outQ[64]);

vector<int> zigzag(const vector<vector<int>>& matrix);
vector<vector<int>> inverseZigzag(const vector<int>& zigzagged, int N, int M);

struct AC {
    int run;
    int size;
    int code;
};

struct DC {
    int size;
    int code;
};
vector<AC> rle_encoding(const vector<int>& ac, int N, int M);
vector<int> rle_decoding(const vector<AC>& rleCodes, int N, int M);
vector<DC> vlc_encoding(const vector<int>& diffs);
vector<int> vlc_decoding(const vector<DC>& vlcData);
vector<int> encodeDC(const vector<int>& dc);
vector<int> decodeDC(const vector<int>& diff);

vector<uc> Huf_encodingDC(const vector<DC>& dc, map<int, string>& hufTable);
vector<uc> Huf_encodingAC(const vector<AC>& ac, map<int, string>& hufTable);
vector<DC> Huf_decodingDC(const vector<uc>& encoded, map<string, int>& reverseTable);
vector<AC> Huf_decodingAC(const vector<uc>& encoded, map<string, int>& reverseTable);

map<string, int> reverse(const map<int, string>& table);
