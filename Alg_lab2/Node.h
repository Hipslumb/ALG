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

	Node(int val) {
		key = val;
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

	Node* search_node(Node* root, int key);

	void insert(int key) { root = insert_node(root, key, nullptr); }
	void delete_n(int key) { root = delete_node(root, key); }

	Node* min_node(Node* root);
	Node* max_node(Node* root);
	int get_height(Node* root);



private:
	Node* create_node(int key);
	Node* insert_node(Node* root, int key, Node* p);
	Node* delete_node(Node* root, int key);
	void delete_tree(Node* node);

}; 
void pre_order(Node* root);
void in_order(Node* root);
void post_order(Node* root);
void print_tree(Node* root, string space, bool left);

void BFS(Node* root);
void DFS(Node* root);
void print_l(Node* root, int l);