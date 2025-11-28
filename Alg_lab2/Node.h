#pragma once

#include <iostream>
#include <String>
#include <fstream>

using std::cout;
using std::cin;
using std::fstream;
using std::ios;
using std::string;
using std::to_string;

enum color
{
	RED, BLACK
};

enum tree
{
	BT, AVL, RB
};

struct Node {
	int key = 0;
	Node* parent;
	Node* left;
	Node* right;
	int balance_factor;
	color color;

	Node(int val) {
		key = val;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		balance_factor = 0;
		color = BLACK;
	}
};

struct form {
	Node* root;
	form() {
		root = nullptr;
	}
	~form() {
		delete_tree(root);
	}
	Node* search_node(Node* root, int key);

	void insert(int key, tree tree) {
		switch (tree) {
		case BT:
			root = insertAVLorBT(root, key, nullptr, BT); break;
		case AVL:
			root = insertAVLorBT(root, key, nullptr, AVL); break;
		//case RB:
			//root = insertAVLorBT(root, key, nullptr, RB); break;
		}
	}
	void delete_n(int key, tree tree) {
		root = delete_node(root, key, tree);
	}

	Node* min_node(Node* root);
	Node* max_node(Node* root);

	//for AVL
	int count_balance(Node* node);
	void update_balance(Node* node);

	void balancing(Node*& node, tree tree);
	void rotate_right(Node*& x, tree tree);
	void rotate_left(Node*& x, tree tree);
	void big_right(Node*& node, tree tree);
	void big_left(Node*& node, tree tree);

	//for Red & Black
	void fix_tree(Node* node, tree tree);
	void red_uncle(Node* node, tree tree);
	void on_oneside(Node*& node, tree tree);
	void not_on_oneside(Node*& node, tree tree);

private:
	Node* create_node(int key);
	Node* insertAVLorBT(Node* root, int key, Node* p, tree tree);
	Node* insertRB(Node* root, int key, Node* p, tree tree);
	Node* delete_node(Node* root, int key, tree tree);
	void delete_tree(Node* node);

}; 
