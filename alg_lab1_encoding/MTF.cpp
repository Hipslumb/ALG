#include "functions.h"

vector<unsigned char> mtf_encoding(vector<unsigned char> data) {
	vector<unsigned char> encoded;
	vector<unsigned char> dict(256);
	for (int i = 0; i < 256; i++) {
		dict[i] = (unsigned char)i;
	}
	for (unsigned char sym : data) {
		auto i = find(dict.begin(), dict.end(), sym);
		int pos = i - dict.begin();

		encoded.push_back((unsigned char)pos);

		dict.erase(i);
		dict.insert(dict.begin(), sym);
	}

	return encoded;
}
vector<unsigned char> mtf_decoding(vector<unsigned char> encoded) {
	vector<unsigned char> decoded;
	vector<unsigned char> dict(256);
	for (int i = 0; i < 256; i++) {
		dict[i] = (unsigned char)i;
	}
	for (unsigned char num : encoded) {
		auto i = dict.begin() + num;
		unsigned char sym = *i;

		decoded.push_back(sym);
		dict.erase(i);
		dict.insert(dict.begin(), sym);
	}
	return decoded;
}