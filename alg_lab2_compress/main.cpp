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
	//createImages("testdata/RGB.png", "testdata/MY");

	/*Image img; img.load("testdata/lena.png");
	

	cout << "Original size: " << img.data_size;

	cout << "\nNew size: " << img.data_size;

	cout << "\nNew size: " << img.data_size;*/

    vector<vector<float>> small = {
        {10, 20},
        {30, 40}
    };

    cout << "2x2:\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << small[i][j] << " ";
        }
        cout << "\n";
    }

    
    auto big = upsampleBlock(small, 4, 4);

    cout << "\n4x4:\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%6.1f ", big[i][j]);
        }
        cout << "\n";
    }

	clock_t end = clock();
	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	cout << "\nTIME: " << time_taken << " seconds.";
	cout << "\n\n";
	return 0;
}