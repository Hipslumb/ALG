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

void FDCT(const double s[N][M], double S[N][M]);
void IDCT(const double S[N][M], double s[N][M]);