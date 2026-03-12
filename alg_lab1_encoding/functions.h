#pragma once
#include "image.h"

void from9_to7();
void HEX(uc a);
void printHEX(const char* name, int max, bool text);
vector<uc> load_data(string file);

bool same_symbol(uc* data, int pos1, int pos2, int bytes);
vector<uc> rle_encoding(vector<uc> data, int Ms, int Mc);
vector<uc> rle_decoding(vector<uc> encoded, int Ms, int Mc);

double entropy(vector<uc> text, int bytes);
void func_H();

vector<uc> mtf_encoding(vector<uc> data);
vector<uc> mtf_decoding(vector<uc> encoded);

map<uc, int> frequency(vector<uc> data);
void save_file(vector<uc> encoded, map<uc, int>& freq);
vector<uc> read_file(map<uc, int>& freq);

map<uc, double> probability(vector<uc> data);
double arith_encoding(vector<uc> data, map<uc, double> prob);


struct BWTnode {
	vector<uc> L;
	int I;
};

void counting_sort(vector<uc>& data, int col);
BWTnode bwt_encoding(vector <uc> data);
vector <uc> bwt_decoding_matrix(BWTnode encoded);
vector <uc> bwt_decoding_LF(BWTnode encoded);
vector<BWTnode> encoding_blocks(vector<uc>& data, int b_size);
vector<uc> decoding_blocks(vector<BWTnode>& blocks);