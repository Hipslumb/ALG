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
	vector<uc> encoded = Huf.Huf_encoding(data);
	cout << "HUFFMAN K = " << (double)data.size() / encoded.size() << "\n";
	save_file(encoded, freq);

	string path = (string)mf + "hufencoded";

	printHEX(path.c_str(), 128, 1);
	cout << "\n\n";
	tree deHuf;
	map<uc, int> load_f;
	encoded = read_file(load_f);
	deHuf.frequency_tree(load_f);
	vector<uc> decoded = Huf.Huf_decoding(encoded);
	for (int i = 0;i < 128;i++)
		HEX(decoded[i]);
	cout << "\n\n";

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
	cout << "\n    original: ";
	for (int i = 0;i < data.size();i++)
		HEX(data[i]);

	cout << "\nLZ77_encoded: ";
	list<LZnode> en_list = lz77_encoding(data, 4);
	/*for (auto e : en_list) {
		cout << "(" << e.offset << "," << e.len << "," << e.next << ")";
	}*/
	int off = 2;int len = 1;
	vector<uc> encoded = pack_lz(en_list, off, len, data.size());
	for (int i = 0;i < encoded.size();i++)
		HEX(encoded[i]);

	cout << "\nLZ77_decoded: ";
	vector<uc> decoded = lz77_decoding(encoded,off,len);
	for (int i = 0;i < decoded.size();i++)
		HEX(decoded[i]);
	cout << "\n";
}
int main() {
	cout << "\n\n";
	//create_raw();
	//RLE();
	//func_H();
	//MTF();
	//Huffman();
	//Arithmetic();
	//BWT();
	LZ();
	cout << "\n\n";
	return 0;
}