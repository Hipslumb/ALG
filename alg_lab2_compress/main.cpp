#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include "fun.h"

void HEX(uc a) {
	cout << "0x" << setw(2) << setfill('0') << hex << (int)a << " ";
}

void dependence(string in, string out) {
	int q = 0; int k = 0;
	string compr_file = "depend.bin";

	ofstream file(out, ios::out);
	for (int i = 0; i < 100; i += 4) {
		if (i != 0) {
			q = i;
			Image img; img.load(in);
			img.compressor(compr_file, q);

			ifstream tmp(compr_file, std::ios::binary | std::ios::ate);
			int comp_size = tmp.tellg(); tmp.close();

			file << q << " " << comp_size << "\n";
		}
	}
	file.close();
}

static string my_rgb = "testdata/MYRGB.png";
static string my_g = "testdata/MYgrey.png";
static string my_bwR = "testdata/MYbw_round.png";
static string my_bwD = "testdata/MYbw_dither.png";

static string lena_rgb = "testdata/LENARGB.png";
static string lena_g = "testdata/LENAgrey.png";
static string lena_bwR = "testdata/LENAbw_round.png";
static string lena_bwD = "testdata/LENAbw_dither.png";

static string my1024_rgb = "testdata/1024RGB.png";
static string my1024_g = "testdata/1024grey.png";
static string my1024_bwR = "testdata/1024bw_round.png";
static string my1024_bwD = "testdata/1024bw_dither.png";


int main() {
	cout << "\n\n";
	string compr_file = "compressed/lena_g.bin";
	int quality = 75;
	clock_t start = clock();
	//createImages("testdata/RGB.png", "testdata/MY");

	Image img; img.load(lena_g);
	double orig_size = img.data_size;
	cout << "Original size: " << orig_size << " byte";

	img.compressor(compr_file, quality);
	clock_t end = clock();

	ifstream file(compr_file, std::ios::binary | std::ios::ate);
	double comp_size = file.tellg();file.close();

	//NO TABLES
	cout << "\nCompressed size: " << comp_size << " byte";

	img.decompressor(compr_file);
	cout << "\nDempressed size: " << img.data_size << " byte";

	cout << "\nK = " << orig_size / comp_size;

	img.savePNG("decompressed/lena_g.png");
	/*string in = lena_g;
	string out = "LENA_G";
	dependence(in, "dependence/" + out);

	clock_t end = clock();*/
	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	cout << "\nTIME: " << time_taken << " seconds.";
	cout << "\n\n";
	cout << endl;
	return 0;
}