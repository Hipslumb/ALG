
#include "fun.h"

vector<uc> downsampling(const vector<uc>& channel, int w, int h, int k) {
	int new_w = w / k;
	int new_h = h / k;
	vector<uc> result(new_w * new_h);

	for (int i = 0; i < new_h; i++) {
		for (int j = 0; j < new_w; j++) {
			int sum = 0;
			for (int dy = 0; dy < k; dy++) {
				for (int dx = 0; dx < k; dx++) {
					int x = j * k + dx;
					int y = i * k + dy;
					sum += channel[y * w + x];
				}
			}
			result[i * new_w + j] = sum / (k * k);
		}
	}
	return result;
}

vector<uc> upsampling(const vector<uc>& channel, int w, int h, int k) {
	int new_w = w * k;
	int new_h = h * k;
	vector<uc> result(new_w * new_h);

	for (int i = 0; i < new_h; i++) {
		for (int j = 0; j < new_w; j++) {
			int srcX = j / k;
			int srcY = i / k;
			result[i * new_w + j] = channel[srcY * w + srcX];
		}
	}
	return result;
}

void testPixelationArtifacts(string filename) {

	int koef[] = { 2, 4, 8, 16 };
	int i = 0;
	for (int k : koef) {
		Image copy;
		copy.load(filename);
		copy.downsampling(k);
		
		copy.upsampling(k);
		copy.savePNG("koef/upsampled_" + to_string(k) + ".png");

	}
}

float linearInterpolation(float x1, float y1, float x2, float y2, float x) {
	if (x < x1 || x > x2) {
		cout << "Warning: x = " << x << " out of range [" << x1 << ", " << x2 << "]" << endl;
	}
	if (x1 == x2)
		return y1;

	float t = (x - x1) / (x2 - x1);
	return y1 + t * (y2 - y1);
}

float linearSpline(const vector<float>& x, const vector<float>& y, float x_val) {
	if (x_val <= x[0]) {
		return linearInterpolation(x[0], y[0], x[1], y[1], x_val);
	}
	if (x_val >= x.back()) {
		int n = x.size() - 1;
		return linearInterpolation(x[n - 1], y[n - 1], x[n], y[n], x_val);
	}
	for (int i = 0; i < (int)x.size() - 1; i++) {
		if (x_val >= x[i] && x_val <= x[i + 1]) {
			return linearInterpolation(x[i], y[i], x[i + 1], y[i + 1], x_val);
		}
	}
	return 0;
}

float bilinearInterpolation(
	float x1, float y1, float x2, float y2,
	float z11, float z12, float z21, float z22, float x, float y) {
	if (x < x1 || x > x2 || y < y1 || y > y2) {
		return 0;
	}
	float z_top = linearInterpolation(x1, z11, x2, z21, x);
	float z_bottom = linearInterpolation(x1, z12, x2, z22, x);

	float result = linearInterpolation(y1, z_top, y2, z_bottom, y);

	return result;
}

vector<vector<float>> upsampleBlock(const vector<vector<float>>& small, int newH, int newW) {
	int oldH = small.size();
	int oldW = small[0].size();

	vector<vector<float>> big(newH, vector<float>(newW));

	for (int y = 0; y < newH; y++) {
		for (int x = 0; x < newW; x++) {
			float Y = (float)y * (oldH - 1) / (newH - 1);
			float X = (float)x * (oldW - 1) / (newW - 1);

			int y1 = (int)Y;
			int x1 = (int)X;
			int y2 = min(y1 + 1, oldH - 1);
			int x2 = min(x1 + 1, oldW - 1);

			float z11 = small[y1][x1];
			float z12 = small[y2][x1];
			float z21 = small[y1][x2];
			float z22 = small[y2][x2];

			float val = bilinearInterpolation(x1, y1, x2, y2, z11, z12, z21, z22, X, Y);

			big[y][x] = val;
		}
	}

	return big;
}

vector<uc> resize(const vector<uc>& channel, int oldW, int oldH, int newW, int newH) {
	vector<vector<float>> oldImage(oldH, vector<float>(oldW));
	for (int y = 0; y < oldH; y++) {
		for (int x = 0; x < oldW; x++) {
			oldImage[y][x] = channel[y * oldW + x];
		}
	}

	vector<vector<float>> newImage = upsampleBlock(oldImage, newH, newW);

	vector<uc> result(newW * newH);
	for (int y = 0; y < newH; y++) {
		for (int x = 0; x < newW; x++) {
			result[y * newW + x] = (uc)min(255.0f, max(0.0f, newImage[y][x]));
		}
	}
	return result;
}