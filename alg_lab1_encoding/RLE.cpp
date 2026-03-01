#define STB_IMAGE_IMPLEMENTATION
#include "functions.h"

unsigned char* rle_encoding(unsigned char* data, int size, int& outsize) {
	unsigned char* encoded = new unsigned char[size * 2];
	int i = 0, pos = 0; outsize = 0;
	while (i < size) {
		int k = 1;
		while (data[i] == data[i + k] && k < 256) {
			k++;
		}
		encoded[pos++] = k;
		encoded[pos++] = data[i];
		outsize += 2;
		i += k;
	}
	return encoded;
}

unsigned char* rle_decoding(unsigned char* encoded, int size, int& outsize) {
	outsize = 0;
	for (int i = 0;i < size;i += 2) {
		outsize += (int)encoded[i];
	}
	unsigned char* decoded = new unsigned char[outsize];

	int i = 0, pos = 0;
	while (i < size) {
		int k = (int)encoded[i];
		for (int j = 0;j < k;j++) {
			decoded[pos++] = encoded[i + 1];
		}
		i += 2;
	}
	return decoded;
}