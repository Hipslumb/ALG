#include "functions.h"

double entropy(vector<uc> text, int bytes) {
	
	int size = text.size() / bytes;
	map<string, int> sym;
	for (int i = 0;i < size;i++) {
		string element;
		for (int j = 0; j < bytes; j++) {
			element += text[i * bytes + j];
		}
		sym[element]++;
	}

	double H = 0; //-sum(pi*log2(pi)

	for (auto& s : sym) {
		double Pi = (double)s.second / size;
		H -= Pi * log2(Pi);
	}

	return H;
}
