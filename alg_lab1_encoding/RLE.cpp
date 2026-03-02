#define STB_IMAGE_IMPLEMENTATION
#include "functions.h"

unsigned char* rle_encoding(unsigned char* data, int size, int& outsize) {
	unsigned char* encoded = new unsigned char[size * 2];
	int i = 0, pos = 0; outsize = 0;
	while (i < size) {
		int k = 1;
		if (i + 1 < size && data[i] == data[i + 1]) {
			while (k < 127 && i + k < size && data[i] == data[i + k]) {
				k++;
			}
			encoded[pos++] = k;
			encoded[pos++] = data[i];
			i += k;
		}
		else {
			while (k < 127 && i + k + 1 < size && data[i + k] != data[i + k + 1]) {
				k++;
			}
			encoded[pos++] = k | 0x80; //or k + 128
			for (int j = 0; j < k; j++) {
				encoded[pos++] = data[i++];
			}
		}
	}
	outsize = pos;
	return encoded;
}

unsigned char* rle_decoding(unsigned char* encoded, int size, int& outsize) {
	outsize = 0;
	
	for (int i = 0; i < size; ) {
		int k = (int)encoded[i];
		if ((k & 0x80) == 0) {
			outsize += k;
			i += 2;
		}
		else {
			outsize += k ^ 0x80;
			i += 1 + (k ^ 0x80);
		}
	}
	unsigned char* decoded = new unsigned char[outsize];

	int i = 0, pos = 0;
	while (i < size) {
		int k = (int)encoded[i];
		if ((k & 0x80) == 0) {
			for (int j = 0; j < k; j++) {
				decoded[pos++] = encoded[i + 1];
			}
			i += 2;
		}
		else {
			for (int j = 0; j < (k ^ 0x80); j++) {
				decoded[pos++] = encoded[i + 1 + j];
			}
			i += (k ^ 0x80) + 1;
		}
	}
	return decoded;
}