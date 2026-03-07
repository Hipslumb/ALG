#pragma once
#include "functions.h"

struct Node {
	uc sym;
	int freq;
	Node* left;
	Node* right;
	Node(uc s, int f) :
		sym(s), freq(f), left(nullptr), right(nullptr) {}
};

struct compare {
	bool operator()(Node* a, Node* b) {
		return a->freq > b->freq;
	}
};

class tree {
	Node* root;
	map<uc, string> codes;

	void clear(Node* node);

public:
	tree() : root(nullptr) {}
	~tree() {
		clear(root);
	}
	void frequency_tree(map<uc, int> freq);
	vector<uc> Huf_encoding(vector<uc> data);
	vector<uc> Huf_decoding(vector<uc> encoded);
	void get_bits(Node* root, string code);

};

inline void tree::clear(Node* node) {
	if (!node) return;
	clear(node->left);
	clear(node->right);
	delete node;
}