#include "functions.h"


void BWT_MTF(vector<uc> data, vector<int>& block_sizes,ofstream& out) {
	//BWT + MTF

	for (int b_size : block_sizes) {
		vector<BWTnode> blocks = encoding_blocks(data, b_size);

		vector<uc> mtf_data;
		for (auto& block : blocks) {
			vector<uc> mtf_result = mtf_encoding(block.L);
			mtf_data.insert(mtf_data.end(),
				mtf_result.begin(),
				mtf_result.end());
		}

		double H = entropy(mtf_data, 1);

		out << b_size << " " << H << "\n";
	}
	
}

void entropy_dependence() {
	vector<uc> data = load_data("encoding/RGB.raw");
	ofstream out("depend/rgb3_H");

	vector<int> block_sizes = {
		//1, 2, 3,
		//4, 8, 12, 16, 24, 32, 48, 64, 96, 128,

		//192, 255, 256,/* 384,*/ 512, 768, 1024,

		///*1536, 2048, 3072, 4096, 6144, 8192,

		//12288, 16384,*/ 24576, 32768, /*49152, 65536,

		//131072,*/ 262144, 524288, 1048576
		48, 96, 192, 384, 768, 1536, 3072, 6144, 12288
	};
	BWT_MTF(data, block_sizes, out);
}

void func_H() {
	vector<uc> eng_text = load_data("encoding/english.txt");
	vector<uc> ru_text= load_data("encoding/Antichnaya mifologiya.txt");

	ofstream f_eng("depend/engEntropy", ios::binary);
	for (int n = 1; n < 128; n++) {
		double H = entropy(eng_text, n);
		f_eng << n << " " << H << "\n";
	}
	ofstream f_ru("depend/ruEntropy", ios::binary);
	for (int n = 1; n < 128; n++) {
		double H = entropy(eng_text, n);
		f_ru << n << " " << H << "\n";
	}
}


void LZSS_compress(vector<uc>& data, vector<int>& buf_sizes, ofstream& out) {
	for (int buf_size : buf_sizes) {
		list<LZ77node> encoded_nodes = lz77_encoding(data, buf_size);
		vector<uc> compressed = pack_lz77(encoded_nodes, 2, 2, data.size());
		double k = (double)data.size() / compressed.size();

		out << buf_size << " " << k << "\n";
	}
}

void LZSS_dependence() {
	vector<uc> data = load_data("encoding/english.txt");
	ofstream out("depend/eng_SS");

	vector<int> buf_sizes = {
		8, 12, 16, 64, 128,

		256, 512, 768, 1024, 4096, 24576, 32768, 49152, 65536

		/*3, 48, 96, 192, 384, 768, 1536, 3072, 6144, 12288, 65538*/
	};
	LZSS_compress(data, buf_sizes, out);
}

void LZW_compress(vector<uc>& data, vector<int>& max_dict, ofstream& out) {
	for (int size : max_dict) {
		list<LZ78node> encoded_nodes = lz78_encoding(data, size);
		vector<uc> compressed = pack_lz78(encoded_nodes, 2, data.size());
		double k = (double)data.size() / compressed.size();

		out << size << " " << k << endl;
	}
}

void LZW_dependence() {
	vector<uc> data = load_data("encoding/RGB.raw");
	ofstream out("depend/rgb_W");

	vector<int> buf_sizes = {
		/*8, 12, 16, 64, 128,

		256, 512, 768, 1024, 4096, 24576, 32768, 49152, 65536*/

		/*48, 96, 192, 384, 768, 1536, 3072, 6144, 12288*/
		9, 15, 63, 258, 1026, 24876, 49152, 65539
	};
	LZW_compress(data, buf_sizes, out);
}
