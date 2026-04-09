#pragma once
#include "Image.h"

void createImages(string filename, string outpath);
void testPixelationArtifacts(string filename);
float linearInterpolation(float x1, float y1, float x2, float y2, float x);
float bilinearInterpolation(
	float x1, float y1, float z11, float y2, float z12,
	float x2, float z21, float z22,
	float x, float y);

float linearSpline(const vector<float>& x, const vector<float>& y, float x_val);

void FDCT(const vector<vector<double>>& s, vector<vector<double>>& S);
void IDCT(const vector<vector<double>>& S, vector<vector<double>>& s);

vector<vector<double>> DCTMatrix(int N);
vector<vector<double>> matrixMultiply(const vector<vector<double>>& A,
	const vector<vector<double>>& B);
vector<vector<double>> matrixTranspose(const vector<vector<double>>& A);
vector<vector<double>> DCT_bymatrix(const vector<vector<double>>& f, bool is_F);
