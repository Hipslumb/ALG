#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include "fun.h"

void HEX(uc a) {
	cout << "0x" << setw(2) << setfill('0') << hex << (int)a << " ";
}

int main() {
	cout << "\n\n";
	clock_t start = clock();

	Image img; img.load("testdata/RGB.png");
	img.to_YCbCr();
	img.saveComponents("test/MY");
	stbi_write_png("test/myYCbCr.png", img.width, img.height, 3, img.data, 0);

	clock_t end = clock();
	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	cout << "\nTIME: " << time_taken << " seconds.";
	cout << "\n\n";
	return 0;
}