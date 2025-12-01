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

class Node {
public:
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
		color = RED;
	}
};

class form {
	Node* root; Node* psevdo;

	Node* create_node(int key);
	Node* search_node(Node* root, int key);


	Node* min_node(Node* root);
	Node* max_node(Node* root);

	void filltree(tree type);
	void searchresult(int key);

	Node* delete_node(Node* root, int key, tree tree);
	void delete_tree(Node* node);

	//for AVL
	int count_balance(Node* node);
	void update_balance(Node* node);
	void balancing(Node*& node, tree tree);

	void rotate_right(Node*& x, tree tree);
	void rotate_left(Node*& x, tree tree);
	void big_right(Node*& node, tree tree);
	void big_left(Node*& node, tree tree);

	//for Red & Black
	int blackHight(Node* node);
	void fix_tree(Node* node);
	Node* insertAVLorBT(Node* root, int key, Node* p, tree tree);
	Node* insertRB(int key);

	void rotate_rightRB(Node* x);
	void rotate_leftRB(Node* x);
	void deleteRB(int key);
	void change_node(Node* x, Node* y);
	
	void fix_delete(Node* x);

	void insert(int key, tree tree) {
		switch (tree) {
		case BT:
			root = insertAVLorBT(root, key, nullptr, BT); break;
		case AVL:
			root = insertAVLorBT(root, key, nullptr, AVL); break;
		case RB:
			root = insertRB(key); break;
		}
	}
	void delete_n(int key, tree tree) {
		root = delete_node(root, key, tree);
	}
public:
	form(tree tree) {
		if (tree == RB) {
			psevdo = new Node(0);
			psevdo->color = BLACK;
			root = psevdo;
		}
		else {
			root = nullptr;
			psevdo = nullptr;
		}
	}
	~form() {
		delete_tree(root);
		if (psevdo != nullptr) {
			delete psevdo;
		}
	}

	void BTtree();
	void AVLtree();
	void RBtree();
}; 
