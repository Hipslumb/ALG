#pragma once
#include "functions.h"

struct Node {
	unsigned char sym;
	int freq;
	Node* left;
	Node* right;
	Node(unsigned char s, int f) :
		sym(s), freq(f), left(nullptr), right(nullptr) {}
};

struct compare {
	bool operator()(Node* a, Node* b) {
		return a->freq > b->freq;
	}
};

class tree {
	Node* root;
	map<unsigned char, string> codes;

	void clear(Node* node);

public:
	tree() : root(nullptr) {}
	~tree() {
		clear(root);
	}
	void frequency_tree(map<unsigned char, int> freq);
	vector<unsigned char> Huf_encoding(vector<unsigned char> data);
	vector<unsigned char> Huf_decoding(vector<unsigned char> encoded);
	void get_bits(Node* root, string code);

};

inline void tree::clear(Node* node) {
	if (!node) return;
	clear(node->left);
	clear(node->right);
	delete node;
}