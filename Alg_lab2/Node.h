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

struct Node {
	int key = 0;
	Node* parent;
	Node* left;
	Node* right;
	int balance_factor;

	Node(int val) {
		key = val;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		balance_factor = 0;
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
	//for BT
	Node* search_node(Node* root, int key);

	void insert(int key) {
		root = insert_node(root, key, nullptr); 
	}
	void delete_n(int key) { 
		root = delete_node(root, key); 
	}

	Node* min_node(Node* root);
	Node* max_node(Node* root);

	//for AVL
	int count_balance(Node* node);
	void update_balance(Node* node);

	void balancing(Node*& node);
	void rotate_right(Node*& x);
	void rotate_left(Node*& x);
	void big_right(Node*& node);
	void big_left(Node*& node);


private:
	Node* create_node(int key);
	Node* insert_node(Node* root, int key, Node* p);
	Node* delete_node(Node* root, int key);
	void delete_tree(Node* node);

}; 
