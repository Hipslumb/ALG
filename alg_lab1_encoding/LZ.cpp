#include "functions.h"

list<LZnode> lz77_encoding(vector<uc> data, int buf_size) {
	list<LZnode> encoded;
	vector<uc> dict;
	int k = 0; LZnode cur;

	while (k < data.size()) {
		vector<uc> buffer;
		for (int j = 0; j < buf_size && j + k < data.size(); j++) {
			buffer.push_back(data[j + k]);
		}
		LZnode cur;
		for (int j = dict.size() - 1;j >= 0;j--) {
			int len = 0;
			while (j + len < dict.size() &&
				len < buffer.size() && dict[j + len] == buffer[len])
				len++;

			if (len > cur.len) {
				cur.len = len;
				cur.offset = dict.size() - j;
			}

		}
		for (int j = 0; j < cur.len + 1 && j < buffer.size(); j++)
			dict.push_back(buffer[j]);
		
		int next_pos = k + cur.len;
		cur.next = (next_pos < data.size()) ? data[next_pos] : 0;

		encoded.push_back(cur);
		k = dict.size();
	}
	return encoded;
}

vector<uc> pack_lz(list<LZnode> data, int off_bytes, int len_bytes, int size) {
	vector<uc> encoded;
	for (int i = 0; i < 4; i++)
		encoded.push_back(static_cast<uc>((size >> (8 * i)) & 0xFF));
	for (auto node : data) {
		int off = node.offset;
		for (int i = 0; i < off_bytes; i++) {
			encoded.push_back(static_cast<uc>(off & 0xff));
			off >>= 8;
		}
		int len = node.len;
		for (int i = 0; i < len_bytes; i++) {
			encoded.push_back(static_cast<uc>(len & 0xff));
			len >>= 8;
		}
		encoded.push_back(node.next);
	}
	return encoded;
}


vector<uc> lz77_decoding(vector<uc> encoded, int off_bytes, int len_bytes) {
	vector<uc> decoded;
	vector<uc> dict;
	int pos = 0; int len;
	int size = 0;

	for (int i = 0; i < 4; i++) {
		size |= (encoded[pos + i] << (8 * i));
		pos++;
	}

	while (pos < encoded.size()) {
		int off = 0;
		for (int i = 0; i < off_bytes; i++) {
			off |= (encoded[pos + i] << (8 * i));
		}
		pos += off_bytes;
		int len = 0;
		for (int i = 0; i < len_bytes; i++) {
			len |= (encoded[pos + i] << (8 * i));
		}
		pos += len_bytes;
		uc next = encoded[pos++];
		if (len > 0) {
			int start = decoded.size() - off;
			for (int i = 0; i < len; i++) {
				decoded.push_back(decoded[start + i]);
			}
		}
		decoded.push_back(next);
	}
	if (decoded.size() > size) {
		decoded.resize(size);
	}
	return decoded;
}