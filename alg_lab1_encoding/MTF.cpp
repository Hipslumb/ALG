#include "functions.h"

vector<uc> mtf_encoding(vector<uc> data) {
	vector<uc> encoded;
	vector<uc> dict(256);
	for (int i = 0; i < 256; i++) {
		dict[i] = (uc)i;
	}
	for (uc sym : data) {
		auto i = find(dict.begin(), dict.end(), sym);
		int pos = i - dict.begin();

		encoded.push_back((uc)pos);

		dict.erase(i);
		dict.insert(dict.begin(), sym);
	}

	return encoded;
}
vector<uc> mtf_decoding(vector<uc> encoded) {
	vector<uc> decoded;
	vector<uc> dict(256);
	for (int i = 0; i < 256; i++) {
		dict[i] = (uc)i;
	}
	for (uc num : encoded) {
		auto i = dict.begin() + num;
		uc sym = *i;

		decoded.push_back(sym);
		dict.erase(i);
		dict.insert(dict.begin(), sym);
	}
	return decoded;
}