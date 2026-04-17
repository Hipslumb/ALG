#pragma once
#include "Header.h"

class Image
{
public:
	int width;
	int height;
	int orig_w;
	int orig_h;
	int pixel; //1 - rw or grey, 3 - RGB
	int type; //0 - rw, 1 - grey, 2 - RGB
	int color_space; // 0 - RGB, 1 - YCbCr
	uc* data;
	int data_size;

	Image() : width(0), height(0), pixel(0),
		type(0), color_space(0), data(nullptr), data_size(0), orig_h(0),orig_w(0) {
	}
	~Image() {
		if (data) stbi_image_free(data);
	};

	bool load(string filename);
	void save(string filename);

	bool loadDATA(const string& filename, vector<uc>& Y_compressed,
		vector<uc>& Cb_compressed, vector<uc>& Cr_compressed, int& quality,
	    int& dc_y, int& dc_cb, int& dc_cr, int& k);

	void saveDATA(string filename, const vector<uc>& Y_compressed,
		const vector<uc>& Cb_compressed, const vector<uc>& Cr_compressed,
		int quality, int dc_y, int dc_cb, int dc_cr, int k);
	void saveJPEG(string outfile);
	void savePNG(string outfile);
	
	void toGrayscale();
	void toBW_byrounding();
	void toBW_byDithering();
	void to_YCbCr();
	void to_RGB();

	void compressor(string outfile, int quality);
	void decompressor(string infile);
	void compressY(string outfile, int quality);
	void decompressY(string infile);
};