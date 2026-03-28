#include "functions.h"
#include <unordered_map>
//here LZSS not LZ77 (i am too lazy to rename all functions)

list<LZ77node> lz77_encoding(vector<uc> data, int buf_size) {
	list<LZ77node> encoded;
	vector<uc> dict;
	int k = 0;

	while (k < data.size()) {
		vector<uc> buffer;
		for (int j = 0; j < buf_size && j + k < data.size(); j++) {
			buffer.push_back(data[j + k]);
		}
		LZ77node cur;
		int search_start = max(0, (int)dict.size() - buf_size);
		for (int j = dict.size() - 1;j >= search_start;j--) {
			int len = 0;
			while (j + len < dict.size() &&
				len < buffer.size() && dict[j + len] == buffer[len])
				len++;

			if (len > cur.len && len >= 2) {
				cur.len = len;
				cur.offset = dict.size() - j;
			}

		}
		if (cur.len >= 2) {
			encoded.push_back({ cur.offset, cur.len, 0 });
			for (int j = 0; j < cur.len; j++) {
				dict.push_back(buffer[j]);
			}
			k += cur.len;
		}
		else {
			encoded.push_back({ 0, 0, data[k] });
			dict.push_back(data[k]);
			k++;
		}
	}
	return encoded;
}

vector<uc> pack_lz77(list<LZ77node> data, int off_bytes, int len_bytes, int size) {
	vector<uc> encoded;
	packing(encoded, size, 4);
	for (auto node : data) {
		if (node.len == 0) {
			encoded.push_back(0);
			encoded.push_back(node.next);
		}
		else {
			encoded.push_back(1);
			packing(encoded, node.offset, off_bytes);
			packing(encoded, node.len, len_bytes);
		}
	}
	return encoded;
}

vector<uc> lz77_decoding(vector<uc> encoded, int off_bytes, int len_bytes) {
	vector<uc> decoded;
	int pos = 0;
	int size = 0;

	unpacking(encoded, size, 4, pos);

	while (pos < encoded.size()) {
		int flag = encoded[pos++];
		if (flag == 0) {
			decoded.push_back(encoded[pos++]);
		}
		else {
			int off = 0;
			unpacking(encoded, off, off_bytes, pos);
			int len = 0;
			unpacking(encoded, len, len_bytes, pos);
			int start = decoded.size() - off;
			for (int i = 0; i < len; i++) 
				decoded.push_back(decoded[start + i]);
				
		}
	}
	if (decoded.size() > size) {
		decoded.resize(size);
	}
	return decoded;
}

//here LZW not LZ78

list<LZ78node> lz78_encoding(vector<uc> data,int max_dict) {
	list<LZ78node> encoded;
	vector<string> dict;
	for (int i = 0;i < 256;i++) {
		dict.push_back(string(1, i));
	}
	string cur = "";

	for (uc c : data) {
		string str = cur + string(1, c);
		
		int index = -1;
		for (int i = 0; i < dict.size();i++)
			if (dict[i] == str) {
				index = i;
				break;
			}
		if (index != -1)
			cur = str;
		else {
			for (int i = 0; i < dict.size();i++)
				if (dict[i] == cur) {
					index = i;
					break;
				}
			encoded.push_back({ index });
			if (dict.size() < max_dict) 
				dict.push_back(str);
			cur = string(1,c);
		}
	}
	int index = 0;
	if (!cur.empty()) {
		for (int i = 0; i < dict.size();i++)
			if (dict[i] == cur) {
				index = i;
				break;
			}
		encoded.push_back({index});
	}
	return encoded;
}

vector<uc> pack_lz78(list<LZ78node> data, int i_bytes, int size) {
	vector<uc> packed;
	packing(packed, size, 4);
	for (auto node : data) {
		packing(packed, node.index, i_bytes);
	}
	return packed;
}

vector<uc> lz78_decoding(vector<uc> encoded, int i_bytes, int max_dict) {
	vector<uc> decoded;
	vector<string> dict;
	for (int i = 0;i < 256;i++) {
		dict.push_back(string(1, i));
	}
	int pos = 0;
	int size = 0;

	unpacking(encoded, size, 4, pos);

	int prev_idx = 0;
	unpacking(encoded, prev_idx, i_bytes, pos);

	string prev_str = dict[prev_idx];
	for (uc c : prev_str) {
		decoded.push_back(c);
	}

	while (pos < encoded.size()) {
		int index = 0;
		unpacking(encoded, index, i_bytes, pos);

		string str;
		if (index < dict.size())
			str = dict[index];
		else
			str = prev_str + prev_str[0];
		for (auto s : str) {
			decoded.push_back(s);
		}

		if (dict.size() < max_dict) {
			dict.push_back(prev_str + str[0]);
		}
		prev_str = str;
	}
	if (decoded.size() > size) {
		decoded.resize(size);
	}
	return decoded;
}