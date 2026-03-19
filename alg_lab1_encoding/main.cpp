#include "Huffman.h"
//#include "image.h"

void create_raw() {
	string path = (string)mf + "Безымянный.png";
	const char* original = path.c_str();
	Image img;

	path = (string)mf + "out.raw";
	const char* raw = path.c_str();

	if (img.load(original)) {
		img.save(raw);
		printHEX(raw, 1000, 0);
	}
	img.compare(original, raw);cout << "\n\n";
}

void RLE() {
	vector<uc> a = {4, 3, 4, 3, 3, 3, 5, 5};
	int Ms = 16, Mc = 16;
	vector<uc> rle_en = rle_encoding(/*img.data*/a, Ms, Mc);
	cout << "RLE encoded:";
	for (int i = 0;i < rle_en.size();i++)
		HEX(rle_en[i]);
	cout << "\n";

	vector<uc> rle_de = rle_decoding(rle_en, Ms, Mc);
	cout << "RLE decoded:";
	for (int i = 0;i < rle_de.size();i++)
		HEX(rle_de[i]);
	cout << "\n\n";
}

void MTF() {
	vector<uc> a = { 'a', 'b', 'a', 'c', 'b', 'a'};
	vector<uc> mtf_en = mtf_encoding(a);
	cout << "MTF encoded:";
	for (int i = 0;i < mtf_en.size();i++)
		HEX(mtf_en[i]);
	cout << "\n";
	vector<uc> mtf_de = mtf_decoding(mtf_en);
	cout << "MTF decoded:";
	for (int i = 0;i < mtf_de.size();i++)
		HEX(mtf_de[i]);
	cout << "\n";

}

void Huffman() {
	vector<uc> data = load_data((string)mf + "english.txt");

	tree Huf;
	map<uc, int> freq = frequency(data);
	Huf.frequency_tree(freq);
	map<uc, uc> lens = Huf.get_len();
	map<uc, string> canon_codes = codes_builder(lens);
	vector<uc> encoded = Huf.Huf_encoding(data, canon_codes);
	cout << "HUFFMAN K = " << (double)data.size() / encoded.size() << "\n";

	save_file(encoded, lens);

	string path = (string)mf + "hufencoded";

	printHEX(path.c_str(), 128, 1);
	cout << "\n\n";



	map<uc, uc> load_lens;
	encoded = read_file(load_lens);
	canon_codes = codes_builder(load_lens);

	vector<uc> decoded = Huf_decoding(encoded,canon_codes);
	for (int i = 0;i < 128;i++)
		HEX(decoded[i]);
	cout << "\n\n";

	if (data.size() == decoded.size()) {
		cout << "SAME SIZE\n";
	}
	else {
		cout << "WRONG SIZE\n";
	}
}

void Arithmetic() {
	
	vector<uc> data = load_data((string)mf + "abcd.txt");
	map<uc, double> prob = probability(data);
	cout << "\nArith_encoded: " << arith_encoding(data, prob);
}

void BWT() {
	vector<uc> data = load_data((string)mf + "abcd.txt");
	BWTnode encoded = bwt_encoding(data);
	cout << "\nBWT_encoded: ";
	for (int i = 0;i < data.size();i++)
		HEX(encoded.L[i]);
	cout << "orig index: " << encoded.I;

	cout << "\nBWT_decoded: ";
	vector<uc> decoded = bwt_decoding_LF(encoded);
	for (int i = 0;i < data.size();i++)
		HEX(decoded[i]);
	cout << "\n";
	//suff_vector(data);
	//find_last(data);

}

void LZ() {
	vector<uc> data = load_data((string)mf + "abcd.txt");

	//LZSS (updated LZ77)
	list<LZ77node> en_list_7 = lz77_encoding(data, 4);
	int off = 2;int len = 1;
	vector<uc> encoded = pack_lz77(en_list_7, off, len, data.size());
	cout << "\nsize: ";
	for (int i = 0;i < 4;i++)
		HEX(encoded[i]);

	cout << "\nLZSS_encoded: ";
	for (int i = 4;i < encoded.size();i++)
		HEX(encoded[i]);

	cout << "\nLZSS_decoded: ";
	vector<uc> decoded = lz77_decoding(encoded,off,len);
	for (int i = 0;i < decoded.size();i++)
		HEX(decoded[i]);
	cout << "\n\n    original: ";
	for (int i = 0;i < data.size();i++)
		HEX(data[i]);
	cout << "\n";

	//LZW (updated LZ78)
	list<LZ78node> en_list_8 = lz78_encoding(data,1024);
	int i_bytes = 2;
	encoded = pack_lz78(en_list_8,i_bytes,data.size());
	cout << "\nsize: ";
	for (int i = 0;i < 4;i++)
		HEX(encoded[i]);
	cout << "\nLZW_encoded: ";
	for (int i = 4;i < encoded.size();i++)
		HEX(encoded[i]);

	cout << "\nLZW_decoded: ";
	decoded = lz78_decoding(encoded,i_bytes,1024);
	for (int i = 0;i < decoded.size();i++)
		HEX(decoded[i]);
	
}

int main() {
	//setlocale(LC_ALL, "RU");
	cout << "\n\n";
	//create_raw();
	//RLE();
	//func_H();
	//MTF();
	Huffman();
	//Arithmetic();
	//BWT();
	//LZ();
	cout << "\n\n";
	return 0;
}