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

vector<int> suff_vector(vector <uc> data);
vector<uc> find_last(vector <uc> data);

void packing(vector<uc>& out, int integer, int bytes);
void unpacking(vector<uc> in, int& integer, int bytes, int& pos);

struct LZ77node {
	int offset = 0;
	int len = 0;
	uc next;
};

list<LZ77node> lz77_encoding(vector<uc> data, int buf_size);
vector<uc> pack_lz77(list<LZ77node> data, int off_bytes, int len_bytes, int size);
vector<uc> lz77_decoding(vector<uc> encoded, int off_bytes, int len_bytes);

struct LZ78node {
	int index;
};
list<LZ78node> lz78_encoding(vector<uc> data, int max_dict);
vector<uc> pack_lz78(list<LZ78node> data, int i_bytes, int size);
vector<uc> lz78_decoding(vector<uc> encoded, int i_bytes, int max_dict);

