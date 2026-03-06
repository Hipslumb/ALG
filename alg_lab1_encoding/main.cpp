#include "Huffman.h"
//#include "image.h"

void create_raw() {
	const char* original = "D:/Documents/Study/2 курс/АЛГ/encoding/Безымянный.png";
	Image img;
	const char* raw = "out.raw";
	if (img.load(original)) {
		img.save(raw);
		printHEX(raw, 1000, 0);
	}
	img.compare(original, raw);cout << "\n\n";
}

void RLE() {
	vector<unsigned char> a = {4, 3, 4, 3, 3, 3, 5, 5};
	int Ms = 16, Mc = 16;
	vector<unsigned char> rle_en = rle_encoding(/*img.data*/a, Ms, Mc);
	cout << "RLE encoded:";
	for (int i = 0;i < rle_en.size();i++)
		HEX(rle_en[i]);
	cout << "\n";

	vector<unsigned char> rle_de = rle_decoding(rle_en, Ms, Mc);
	cout << "RLE decoded:";
	for (int i = 0;i < rle_de.size();i++)
		HEX(rle_de[i]);
	cout << "\n\n";
}

void MTF() {
	vector<unsigned char> a = { 'a', 'b', 'a', 'c', 'b', 'a'};
	vector<unsigned char> mtf_en = mtf_encoding(a);
	cout << "MTF encoded:";
	for (int i = 0;i < mtf_en.size();i++)
		HEX(mtf_en[i]);
	cout << "\n";
	vector<unsigned char> mtf_de = mtf_decoding(mtf_en);
	cout << "MTF decoded:";
	for (int i = 0;i < mtf_de.size();i++)
		HEX(mtf_de[i]);
	cout << "\n";

}

void Huffman() {
	ifstream out("D:/Documents/Study/2 курс/АЛГ/encoding/english.txt", ios::binary);
	vector<unsigned char> data; char cur;
	while (out.get(cur))
		data.push_back((unsigned char)cur);

	tree Huf;
	map<unsigned char, int> freq = frequency(data);
	Huf.frequency_tree(freq);
	vector<unsigned char> encoded = Huf.Huf_encoding(data);
	cout << "HUFFMAN K = " << (double)data.size() / encoded.size() << "\n";
	save_file(encoded, freq);

	printHEX("D:/Documents/Study/2 курс/АЛГ/encoding/hufencoded",128, 1);
	cout << "\n\n";
	tree deHuf;
	map<unsigned char, int> load_f;
	encoded = read_file(load_f);
	deHuf.frequency_tree(load_f);
	vector<unsigned char> decoded = Huf.Huf_decoding(encoded);
	for (int i = 0;i < 128;i++)
		HEX(decoded[i]);
	cout << "\n\n";
	out.close();
}

int main() {

	//create_raw();
	//RLE();
	//func_H();
	//MTF();
	//Huffman();
	return 0;
}