#include "functions.h"

bool same_symbol(uc* data, int pos1, int pos2, int bytes) {
	for (int i = 0; i < bytes; i++)
		if (data[pos1 + i] != data[pos2 + i])
			return false;
	return true;
}

vector<uc> rle_encoding(vector<uc> data, int Ms, int Mc) {
	vector<uc> encoded;
	int i = 0; int size = data.size();

	int Ms_byte = Ms / 8; int Mc_byte = Mc / 8;
	int max_count = (1 << (Mc - 1)) - 1;

	while (i < size) {
		int k = 1;
		if (i + Ms_byte < size && same_symbol(data.data(), i, i + Ms_byte, Ms_byte)) {

			while (k < max_count && i + (k + 1) * Ms_byte <= size
				&& same_symbol(data.data(), i, i + k * Ms_byte, Ms_byte))
				k++;

			for (int b = 0; b < Mc_byte; b++)
				encoded.push_back((k >> (8 * (Mc_byte - 1 - b))) & 0xFF);

			for (int b = 0; b < Ms_byte; b++)
				encoded.push_back(data[i + b]);

		}
		else {
			while (k < max_count && i + (k + 1) * Ms_byte <= size
				&& !same_symbol(data.data(), i + k * Ms_byte, i + (1 + k) * Ms_byte, Ms_byte))
				k++;

			int flag = k | (1 << (Mc - 1));
			for (int b = Mc_byte - 1; b >= 0; b--)
				encoded.push_back((flag >> (8 * b)) & 0xFF);


			for (int j = 0; j < k; j++)
				for (int b = 0;b < Ms_byte;b++)
					encoded.push_back(data[i + j * Ms_byte + b]);

		}
		i += k * Ms_byte;
	}
	return encoded;
}

vector<uc> rle_decoding(vector<uc> encoded, int Ms, int Mc) {

	int Ms_byte = Ms / 8; int Mc_byte = Mc / 8;
	vector<uc> decoded;

	int i = 0, pos = 0; int size = encoded.size();
	while (i < size) {
		int k = 0;
        for (int b = 0; b < Mc_byte; b++) {
            k = (k << 8) | encoded[i + b];
        }
		i += Mc_byte;

		int flag = 1 & (k >> (Mc - 1));
		if (flag == 0) {//repeat
			
			for (int j = 0; j < k; j++) {
				for (int b = 0; b < Ms_byte; b++)
					decoded.push_back(encoded[i + b]);
			}
			i += Ms_byte;
		}
		else {
			int len = (k & ((1 << (Mc - 1)) - 1));
			for (int j = 0; j < len; j++) {
				for (int b = 0; b < Ms_byte; b++)
					decoded.push_back(encoded[i + b + j * Ms_byte]);
			}
			i += Ms_byte * len;
		}
	}
	return decoded;
}