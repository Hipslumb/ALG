#include "Another.h"

Node* form::insertRB(Node* root, int key, Node* p, tree tree) {
	return root;
}

void form::fix_tree(Node* node, tree tree) {

	Node* cur = node;
	//if (node->parent->color == BLACK) return;
	while (cur->parent != nullptr && cur->parent->color == RED) {
		Node* parent = cur->parent;
		Node* grand = parent->parent; 
		if (grand == nullptr) return;
		Node* uncle = (parent == grand->left) ? grand->right : grand->left;

		if (uncle != nullptr && uncle->color == RED) {
			red_uncle(cur, tree);
			cur = grand;
		}
		else if (parent == grand->left && cur == parent->left) {
			on_oneside(cur, tree); cur = parent;
		}
		else if (parent == grand->right && cur == parent->right) {
			on_oneside(cur, tree); cur = parent;
		}
		else {
			not_on_oneside(cur, tree); cur = parent;
		}
	}
	
	while (node->parent != nullptr) node = node->parent;
	node->color = BLACK;
}

void form::red_uncle(Node* node, tree tree) {
	Node* parent = node->parent;
	if (parent == nullptr) return;
	Node* grand = parent->parent;
	if (grand == nullptr) return;
	Node* uncle = (parent == grand->left) ? grand->right : grand->left;
	if (uncle == nullptr) return;

	parent->color = BLACK;
	uncle->color = BLACK;
	grand->color = RED;

	if (grand->parent != nullptr && grand->parent->color == RED) fix_tree(grand, tree);

}

void form::on_oneside(Node*& node, tree tree) {
	Node* parent = node->parent;
	if (parent == nullptr) return;
	Node* grand = parent->parent;
	if (grand == nullptr) return;

	parent->color = BLACK;
	grand->color = RED;

	if (parent == grand->left) rotate_right(grand,tree);
	else rotate_left(grand,tree);

	node = parent;
}

void form::not_on_oneside(Node*& node, tree tree) {
	Node* parent = node->parent;
	if (parent == nullptr) return;
	Node* grand = parent->parent;
	if (grand == nullptr) return;

	if (node == parent->right) rotate_left(parent,tree);
	else rotate_right(parent,tree);
	on_oneside(parent, tree);

	node = parent;
}