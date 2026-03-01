#pragma once
#include "image.h"

unsigned char* rle_encoding(unsigned char* data, int size, int& outsize);
unsigned char* rle_decoding(unsigned char* encoded, int size, int& outsize);

