#pragma once
#include "image.h"

void from9_to7();
void HEX(unsigned char a);
void printHEX(const char* name, int max, bool text);

bool same_symbol(unsigned char* data, int pos1, int pos2, int bytes);
vector<unsigned char> rle_encoding(vector<unsigned char> data, int Ms, int Mc);
vector<unsigned char> rle_decoding(vector<unsigned char> encoded, int Ms, int Mc);

double entropy(vector<unsigned char> text, int bytes);
void func_H();

vector<unsigned char> mtf_encoding(vector<unsigned char> data);
vector<unsigned char> mtf_decoding(vector<unsigned char> encoded);

map<unsigned char, int> frequency(vector<unsigned char> data);
void save_file(vector<unsigned char> encoded, map<unsigned char, int>& freq);
vector<unsigned char> read_file(map<unsigned char, int>& freq);
