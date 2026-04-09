
#include "fun.h"

void Image::downsampling(int k) {
	if (width % k != 0 || height % k != 0 || !data) return;

	int new_width = width / k;
	int new_height = height / k;
	int new_size = new_width * new_height;

	uc* new_data = new uc[new_size * pixel];

	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++) {
			int x = j * k;
			int y = i * k;

			for (int c = 0; c < pixel; c++)
				new_data[(i * new_width + j) * pixel + c]
				= data[(y * width + x) * pixel + c];
		}
	}
	stbi_image_free(data);
	data = new_data;
	width = new_width;
	height = new_height;
	data_size = new_size * pixel;
}

void Image::upsampling(int k) {

	int new_width = width * k;
	int new_height = height * k;
	int new_size = new_width * new_height;

	uc* new_data = new uc[new_size * pixel];

	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++) {
			int x = j / k;
			int y = i / k;

			for (int c = 0; c < pixel; c++)
				new_data[(i * new_width + j) * pixel + c]
				= data[(y * width + x) * pixel + c];
		}
	}
	stbi_image_free(data);
	data = new_data;
	width = new_width;
	height = new_height;
	data_size = new_size * pixel;
}

void testPixelationArtifacts(string filename) {

	int koef[] = { 2, 4, 8, 16 };
	int i = 0;
	for (int k : koef) {
		Image copy;
		copy.load(filename);
		copy.downsampling(k);
		//copy.savePNG("koef/" + to_string(i) + "downsampled_" + to_string(k) + ".png");

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
	float x1, float y1, float z11, float y2, float z12,
	float x2, float z21, float z22,
	float x, float y) {
	if (x < x1 || x > x2 || y < y1 || y > y2) {
		return 0;
	}
	float z_top = linearInterpolation(x1, z11, x2, z21, x);
	float z_bottom = linearInterpolation(x1, z12, x2, z22, x);

	float result = linearInterpolation(y1, z_top, y2, z_bottom, y);

	return result;
}
