#include "functions.h"

map<uc, double> probability(vector<uc> data) {
	map<uc, int> freq = frequency(data);
	map<uc, double> prob;
	for (auto& f : freq) {
		uc sym = f.first;
		double Pi = (double)f.second / data.size();
		prob[sym] = Pi;
	}
	return prob;
}

double arith_encoding(vector<uc> data, map<uc, double> prob) {
	double left = 0, right = 1;
	for (uc sym : data) {
		double len = right - left;
		double low = 0;
		for (auto& p : prob) {
			if (p.first == sym) break;
			low += p.second;
		}
		double high = low + prob[sym];
		left = left + len * low;
		right = left + len * high;
		if (left == right) {
			cout << "LEFT == RIGHT when len = " << data.size();
			return left;
		}
	}
	double num = 0, bit = 0.5;
	while (1) {
		if (num + bit < right) {
			if (num + bit >= left) {
				return num + bit;
			}
			num += bit;
		}
		bit /= 2;
		if (bit <= 1e-15)break;
	}
	return (right - left) / 2;
}