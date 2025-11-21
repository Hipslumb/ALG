#pragma once

#include <iostream>
#include <String>
#include <fstream>

using std::cout;
using std::cin;
using std::fstream;
using std::ios;
using std::string;

struct Node {
	int num = 0;
	Node* parent;
	Node* left;
	Node* right;

	Node(int val) {
		num = val;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
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

	Node* create_node(int num);
	Node* search_node(Node* root, int key);
	Node* insert_node(Node* root, int num, Node* p);

	Node* min_node(Node* root);
	Node* max_node(Node* root);
	Node* delete_node(Node* root, int key);

	void delete_tree(Node* node);

	int get_height(Node* root);

}; 
void pre_order(Node* node);
void in_order(Node* node);
void post_order(Node* node);
void print_tree(Node* root, string space, bool left);