#include "Huffman.h"

void HA_compress(string filename, int& orig_size, string out) {
	vector<uc> data = load_data(filename);
	orig_size = data.size();
	tree Huf;
	map<uc, int> freq = frequency(data);
	Huf.frequency_tree(freq);
	map<uc, uc> lens = Huf.get_len();
	map<uc, string> canon_codes = codes_builder(lens);
	vector<uc> encoded = Huf.Huf_encoding(data, canon_codes);

	save_file(out,encoded, lens);
	
	cout << "HA compress K = " << double(data.size()) / encoded.size();
	cout << "\nH = " << entropy(encoded, 1);
}

vector<uc> HA_decompress(string filename) {
	map<uc, uc> load_lens;
	vector<uc> encoded = read_file(filename, load_lens);
	map<uc, string> canon_codes = codes_builder(load_lens);

	vector<uc> decoded = Huf_decoding(encoded, canon_codes);

	return decoded;
}

void RLE_compress(string filename,int& orig_size, string out) {
	vector<uc> data = load_data(filename); orig_size = data.size();
	orig_size = data.size();
	int Ms = 8, Mc = 8;

	vector<uc> rle_en = rle_encoding(data, Ms, Mc);

	vector<uc> encoded;
	packing(encoded, Ms, 1);
	packing(encoded, Mc, 1);
	
	encoded.insert(encoded.end(), rle_en.begin(), rle_en.end());

	save_data(encoded, out);
	cout << "RLE compress K = " << double(data.size()) / encoded.size();
}

vector<uc> RLE_decompress(string filename) {
	int Ms = 0, Mc = 0, pos = 0;
	vector<uc> encoded = load_data(filename);
	unpacking(encoded, Ms, 1, pos);
	unpacking(encoded, Mc, 1, pos);
	
	vector<uc> rle_data(encoded.begin() + pos, encoded.end());

	vector<uc> rle_de = rle_decoding(rle_data, Ms, Mc);

	return rle_de;
}

void BWT_RLE_compress(string filename, int& orig_size, string out) {
	vector<uc> data = load_data(filename);
	int BLOCK_SIZE = 262144;
	int Ms = 8;
	int Mc = 16;
	vector<BWTnode> blocks = encoding_blocks(data, BLOCK_SIZE);
	vector<uc> encoded;

	packing(encoded, BLOCK_SIZE, 4);
	packing(encoded, Ms, 1);
	packing(encoded, Mc, 1);
	packing(encoded, (int)blocks.size(), 4);

	for (auto& block : blocks) {
		packing(encoded, block.I, 4);
		vector<uc> rle_en = rle_encoding(block.L, Ms, Mc);

		packing(encoded, (int)rle_en.size(), 4);
		encoded.insert(encoded.end(), rle_en.begin(), rle_en.end());
	}
	cout << "\n" << entropy(encoded, 1)<< "\n";
	save_data(encoded, out);
	orig_size = data.size();
	cout << "BWT + RLE compress K = " << double(data.size()) / encoded.size();
}

vector<uc> BWT_RLE_decompress(string filename) {
	vector<uc> input = load_data(filename);
	int pos = 0;
	int BLOCK_SIZE = 0;
	unpacking(input, BLOCK_SIZE, 4, pos);
	int Ms = 0, Mc = 0;
	unpacking(input, Ms, 1, pos);
	unpacking(input, Mc, 1, pos);
	int num_blocks = 0;
	unpacking(input, num_blocks, 4, pos);

	vector<BWTnode> blocks;

	for (int i = 0; i < num_blocks; i++) {
		int I = 0;
		unpacking(input, I, 4, pos);

		int rle_size = 0;
		unpacking(input, rle_size, 4, pos);

		vector<uc> rle_data(input.begin() + pos,
			input.begin() + pos + rle_size);
		pos += rle_size;

		vector<uc> L = rle_decoding(rle_data, Ms, Mc);

		blocks.push_back({ L, I });
		
	}

	vector<uc> decoded = decoding_blocks(blocks);

	return decoded;
}

void BWT_MTF_HA_compress(string filename, int& orig_size, string out) {
	vector<uc> data = load_data(filename);
	orig_size = data.size();
	int BLOCK_SIZE = 262144;

	vector<BWTnode> blocks = encoding_blocks(data, BLOCK_SIZE);

	vector<uc> mtf_data;
	for (auto& block : blocks) {
		vector<uc> mtf_result = mtf_encoding(block.L);
		mtf_data.insert(mtf_data.end(), mtf_result.begin(), mtf_result.end());
	}

	map<uc, int> freq = frequency(mtf_data);
	tree Huf;
	Huf.frequency_tree(freq);
	map<uc, uc> lens = Huf.get_len();
	map<uc, string> canon_codes = codes_builder(lens);
	vector<uc> huf_encoded = Huf.Huf_encoding(mtf_data, canon_codes);
	save_file("temp_huffman.bin", huf_encoded, lens);
	vector<uc> encoded;
	packing(encoded, BLOCK_SIZE, 4);
	packing(encoded, (int)blocks.size(), 4);

	for (auto& block : blocks) {
		packing(encoded, block.I, 4);
	}

	vector<uc> huf_file = load_data("temp_huffman.bin");
	encoded.insert(encoded.end(), huf_file.begin(), huf_file.end());

	save_data(encoded, out);
	cout << "BWT+MTF+HA compress K = " << double(data.size()) / encoded.size() << endl;
}

vector<uc> BWT_MTF_HA_decompress(string filename) {
	vector<uc> input = load_data(filename);
	int pos = 0;

	int BLOCK_SIZE = 0;
	unpacking(input, BLOCK_SIZE, 4, pos);

	int num_blocks=0;
	unpacking(input, num_blocks, 4, pos);

	vector<int> indices(num_blocks);
	for (int i = 0; i < num_blocks; i++) {
		unpacking(input, indices[i], 4, pos);
	}

	vector<uc> huf_file(input.begin() + pos, input.end());
	save_data(huf_file, "temp_huffman.bin");

	map<uc, uc> lens;
	vector<uc> huf_encoded = read_file("temp_huffman.bin", lens);
	map<uc, string> canon = codes_builder(lens);
	vector<uc> mtf_data = Huf_decoding(huf_encoded, canon);
	int mtf_pos = 0;
	vector<BWTnode> blocks;

	for (int i = 0; i < num_blocks; i++) {
		int block_len = BLOCK_SIZE;
		if (i == num_blocks - 1) {
			block_len = mtf_data.size() - mtf_pos;
		}

		vector<uc> L_mtf(mtf_data.begin() + mtf_pos,
			mtf_data.begin() + mtf_pos + block_len);
		mtf_pos += block_len;

		vector<uc> L = mtf_decoding(L_mtf);

		blocks.push_back( { L, indices[i] });
	}
	vector<uc> decoded = decoding_blocks(blocks);

	return decoded;
}

void LZSS_compress(string filename, int& orig_size, string out) {
	vector<uc> data = load_data(filename);
	orig_size = data.size();
	list<LZ77node> list = lz77_encoding(data, 4096);
	int off = 2;int len = 2;

	vector<uc> encoded;
	packing(encoded, off, 1);
	packing(encoded, len, 1);

	vector<uc> lzss_data = pack_lz77(list, off, len, data.size());
	encoded.insert(encoded.end(), lzss_data.begin(), lzss_data.end());

	cout << "LZSS compress K = " << double(data.size()) / encoded.size();
	save_data(encoded, out);
}

vector<uc> LZSS_decompress(string filename) {
	vector<uc> encoded = load_data(filename);
	
	int off = 0, len = 0, pos = 0;
	unpacking(encoded, off, 1, pos);
	unpacking(encoded, len, 1, pos);
	vector<uc> data(encoded.begin() + pos, encoded.end());
	vector<uc> decoded = lz77_decoding(data, off, len);

	return decoded;
}

void LZSS_HA_compress(string filename, int& orig_size, string out) {
	vector<uc> data = load_data(filename);
	orig_size = data.size();

	int buf_size = 4096;
	int off_bytes = 2;
	int len_bytes = 2;
	list<LZ77node> lzss_list = lz77_encoding(data, buf_size);
	vector<uc> lzss_data = pack_lz77(lzss_list, off_bytes, len_bytes, data.size());

	map<uc, int> freq = frequency(lzss_data);
	tree Huf;
	Huf.frequency_tree(freq);
	map<uc, uc> lens = Huf.get_len();
	map<uc, string> canon = codes_builder(lens);
	vector<uc> ha_encoded = Huf.Huf_encoding(lzss_data, canon);


	save_file("temp_huffman.bin", ha_encoded, lens);

	vector<uc> output;
	packing(output, off_bytes, 1);
	packing(output, len_bytes, 1);
	packing(output, buf_size, 4);

	vector<uc> huf_file = load_data("temp_huffman.bin");
	output.insert(output.end(), huf_file.begin(), huf_file.end());

	save_data(output, out);
	cout << "LZSS + HA compress K = " << double(data.size()) / output.size() << endl;
}

vector<uc> LZSS_HA_decompress(string filename) {
	vector<uc> input = load_data(filename);
	int pos = 0;

	int off_bytes = 0, len_bytes = 0, buf_size = 0;
	unpacking(input, off_bytes, 1, pos);
	unpacking(input, len_bytes, 1, pos);
	unpacking(input, buf_size, 4, pos);

	vector<uc> huf_data(input.begin() + pos, input.end());
	save_data(huf_data, "temp_huffman.bin");

	map<uc, uc> lens;
	vector<uc> ha_encoded = read_file("temp_huffman.bin", lens);
	map<uc, string> canon = codes_builder(lens);
	vector<uc> lzss_data = Huf_decoding(ha_encoded, canon);

	vector<uc> decoded = lz77_decoding(lzss_data, off_bytes, len_bytes);

	return decoded;
}

void LZW_compress(string filename, int& orig_size, string out) {
	vector<uc> data = load_data(filename);
	orig_size = data.size();
	int max_dict = 65536;
	list<LZ78node> list = lz78_encoding(data, max_dict);
	int i_bytes = 2;

	vector<uc> encoded;
	packing(encoded, i_bytes, 1);
	packing(encoded, max_dict, 4);

	vector<uc> lzw_data = pack_lz78(list, i_bytes, data.size());
	encoded.insert(encoded.end(), lzw_data.begin(), lzw_data.end());

	cout << "LZW compress K = " << double(data.size()) / encoded.size();
	save_data(encoded, out);
}

vector<uc> LZW_decompress(string filename) {
	vector<uc> encoded = load_data(filename);

	int i_bytes = 0, max_dict = 0, pos = 0;
	unpacking(encoded, i_bytes, 1, pos);
	unpacking(encoded, max_dict, 4, pos);
	vector<uc> data(encoded.begin() + pos, encoded.end());
	vector<uc> decoded = lz78_decoding(data, i_bytes, max_dict);

	return decoded;
}

void LZW_HA_compress(string filename, int& orig_size, string out) {
	vector<uc> data = load_data(filename);
	orig_size = data.size();

	int max_dict = 24576;
	int i_bites = 2;
	list<LZ78node> lzw_list = lz78_encoding(data, max_dict);
	vector<uc> lzw_data = pack_lz78(lzw_list, i_bites, data.size());

	map<uc, int> freq = frequency(lzw_data);
	tree Huf;
	Huf.frequency_tree(freq);
	map<uc, uc> lens = Huf.get_len();
	map<uc, string> canon = codes_builder(lens);
	vector<uc> ha_encoded = Huf.Huf_encoding(lzw_data, canon);

	save_file("temp_huffman.bin", ha_encoded, lens);

	vector<uc> output;
	packing(output, i_bites, 1);
	packing(output, max_dict, 4);

	vector<uc> huf_file = load_data("temp_huffman.bin");
	output.insert(output.end(), huf_file.begin(), huf_file.end());

	save_data(output, out);
	cout << "LZW + HA compress K = " << double(data.size()) / output.size() << endl;
}

vector<uc> LZW_HA_decompress(string filename) {
	vector<uc> input = load_data(filename);
	int pos = 0;

	int i_bytes = 0, max_dict = 0;
	unpacking(input, i_bytes, 1, pos);
	unpacking(input, max_dict, 4, pos);

	vector<uc> huf_data(input.begin() + pos, input.end());
	save_data(huf_data, "temp_huffman.bin");

	map<uc, uc> lens;
	vector<uc> ha_encoded = read_file("temp_huffman.bin", lens);
	map<uc, string> canon = codes_builder(lens);
	vector<uc> lzw_data = Huf_decoding(ha_encoded, canon);

	vector<uc> decoded = lz78_decoding(lzw_data, i_bytes, max_dict);

	return decoded;
}

void BWT_MTF_RLE_HA_compress(string filename, int& orig_size, string out) {
	vector<uc> data = load_data(filename);
	orig_size = data.size();
	int BLOCK_SIZE = 262144;
	int Ms = 48;
	int Mc = 16;

	vector<BWTnode> blocks = encoding_blocks(data, BLOCK_SIZE);

	vector<uc> mtf_data;
	for (auto& block : blocks) {
		vector<uc> mtf_result = mtf_encoding(block.L);
		mtf_data.insert(mtf_data.end(), mtf_result.begin(), mtf_result.end());
	}
	vector<uc> rle_data = rle_encoding(mtf_data, Ms, Mc);
	map<uc, int> freq = frequency(rle_data);
	tree Huf;
	Huf.frequency_tree(freq);
	map<uc, uc> lens = Huf.get_len();
	map<uc, string> canon = codes_builder(lens);
	vector<uc> ha_encoded = Huf.Huf_encoding(rle_data, canon);
	save_file("temp_huffman.bin", ha_encoded, lens);

	vector<uc> output;

	packing(output, BLOCK_SIZE, 4);
	packing(output, (int)blocks.size(), 4);

	for (auto& block : blocks) {
		packing(output, block.I, 4);
	}

	packing(output, Ms, 1);
	packing(output, Mc, 1);

	vector<uc> huf_file = load_data("temp_huffman.bin");
	output.insert(output.end(), huf_file.begin(), huf_file.end());

	save_data(output, out);
	cout << "BWT+MTF+RLE+HA compress K = " << double(data.size()) / output.size() << endl;
}

vector<uc> BWT_MTF_RLE_HA_decompress(string filename) {
	vector<uc> input = load_data(filename);
	int pos = 0;
	int BLOCK_SIZE = 0;
	unpacking(input, BLOCK_SIZE, 4, pos);

	int num_blocks = 0;
	unpacking(input, num_blocks, 4, pos);

	vector<int> indices(num_blocks);
	for (int i = 0; i < num_blocks; i++) {
		unpacking(input, indices[i], 4, pos);
	}

	int Ms = 0, Mc = 0;
	unpacking(input, Ms, 1, pos);
	unpacking(input, Mc, 1, pos);
	vector<uc> huf_data(input.begin() + pos, input.end());
	save_data(huf_data, "temp_huffman.bin");

	map<uc, uc> lens;
	vector<uc> ha_encoded = read_file("temp_huffman.bin", lens);
	map<uc, string> canon = codes_builder(lens);
	vector<uc> rle_data = Huf_decoding(ha_encoded, canon);

	vector<uc> mtf_data = rle_decoding(rle_data, Ms, Mc);

	vector<BWTnode> blocks;
	int mtf_pos = 0;

	for (int i = 0; i < num_blocks; i++) {
		int block_len = BLOCK_SIZE;
		if (i == num_blocks - 1) {
			block_len = mtf_data.size() - mtf_pos;
		}
		vector<uc> L_mtf(mtf_data.begin() + mtf_pos,
			mtf_data.begin() + mtf_pos + block_len);
		mtf_pos += block_len;
		vector<uc> L = mtf_decoding(L_mtf);

		blocks.push_back({ L, indices[i] });
	}
	vector<uc> decoded = decoding_blocks(blocks);

	return decoded;
}