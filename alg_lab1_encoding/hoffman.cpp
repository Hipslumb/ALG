#include "Huffman.h"

map<uc, int> frequency(vector<uc> data) {
	map<uc, int> freq;
	for (uc sym : data) {
		freq[sym]++;
	}
	return freq;
}

void tree::get_bits(Node* root, string code) {
	if (!root) return;

	if (!root->left && !root->right) {
		codes[root->sym] = code;
		return;
	}

	get_bits(root->left, code + "0");
	get_bits(root->right, code + "1");
}

void tree::frequency_tree(map<uc, int> freq) {
	priority_queue<Node*, vector<Node*>, compare> queue;
	for (auto p : freq) {
		queue.push(new Node(p.first, p.second));
	}
	while (queue.size() > 1) {
		Node* left = queue.top(); queue.pop();
		Node* right = queue.top(); queue.pop();

		Node* parent = new Node(0, left->freq + right->freq);
		parent->left = left; parent->right = right;
		queue.push(parent);
	}
	root = queue.top();
	codes.clear();
	get_bits(root, "");
}

vector<uc> tree::Huf_encoding(vector<uc> data) {
	vector<uc> encoded;
	string bits;
	for (auto b : data) {
		bits += codes[b];
	}
	int last_size = ((bits.size() % 8) == 0)? 8 : (bits.size() % 8);
	encoded.push_back(last_size);

	for (int i = 0; i < bits.size(); i += 8) {
		uc byte = 0;
		for (int j = 0; j < 8 && i + j < bits.size();j++)
			if (bits[i + j] == '1')
				byte |= (1 << (7 - j));

		encoded.push_back(byte);
	}

	return encoded;
}

vector<uc> tree::Huf_decoding(vector<uc> encoded) {
	vector<uc> decoded;
	int last_size = encoded[0];
	string bits;
	for (int i = 1; i < encoded.size(); i++) {
		uc b = encoded[i];
		for (int j = 7; j >= 0; j--) {
			bits += ((b >> j) & 1) ? '1' : '0';
		}
	}
	if (last_size < 8) {
		bits = bits.substr(0, bits.size() - (8 - last_size));
	}
	Node* cur = root;
	for (char bit : bits) {
		if (bit == '0')
			cur = cur->left;
		else
			cur = cur->right;
		if (!cur->left && !cur->right) {
			decoded.push_back(cur->sym);
			cur = root;
		}
	}
	return decoded;
}

void save_file(vector<uc> encoded, map<uc, int>& freq) {
	ofstream file((string)mf + "hufencoded", ios::binary);
	int size = freq.size();
	file.write((char*)&size, sizeof(size));
	for (auto& p : freq) {
		file.write((char*)&p.first, sizeof(p.first));
		file.write((char*)&p.second, sizeof(p.second));
	}
	int en_size = encoded.size();
	file.write((char*)&en_size, sizeof(en_size));
	file.write((char*)encoded.data(), en_size);

	file.close();
}

vector<uc> read_file(map<uc, int>& freq) {
	ifstream file((string)mf + "hufencoded", ios::binary);
	vector<uc> encoded;

	int size;
	file.read((char*)&size, sizeof(size));
	for (int i = 0; i < size; i++) {
		uc sym;
		int f;
		file.read((char*)&sym, sizeof(sym));
		file.read((char*)&f, sizeof(f));
		freq[sym] = f;
	}
	int en_size;
	file.read((char*)&en_size, sizeof(en_size));
	encoded.resize(en_size);
	file.read((char*)encoded.data(), en_size);

	file.close();
	return encoded;
}