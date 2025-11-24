#include "Another.h"

int form::count_balance(Node* node) {
	if (node == nullptr) return 0;
	int height_left = get_height(node->left);
	int height_right = get_height(node->right);

	return height_left - height_right;
}

void form::update_balance(Node* node) {
	if (node != nullptr) {
		node->balance_factor = count_balance(node);
		update_balance(node->left);
		update_balance(node->right);
	}
}

void form::balancing(Node*& node) {
	if (node == nullptr) return;
	update_balance(node);

	if (node->balance_factor > 1) {
		if (node->left->balance_factor >= 0) rotate_right(node);
		else big_right(node);
	}
	else if (node->balance_factor < -1) {
		if (node->right->balance_factor <= 0) rotate_left(node);
		else big_left(node);
	}
	balancing(node->left);
	balancing(node->right);

	node->balance_factor = count_balance(node);
}

void form::rotate_right(Node*& x) {
	if (x->left == nullptr) return;

	Node* y = x->left;
	x->left = y->right;

	Node* tmp = y->right;

	y->right = x;
	x->left = tmp;

	if (tmp != nullptr) tmp->parent = x;

	y->parent = x->parent;
	x->parent = y;
	update_balance(x);
	update_balance(y);
	x = y;
}

void form::rotate_left(Node*& x) {
	if (x->right == nullptr) return;
	Node* y = x->right;
	x->right = y->left;
	Node* tmp = y->left;

	y->left = x;
	x->right = tmp;

	if (tmp != nullptr) tmp->parent = x;

	y->parent = x->parent;
	x->parent = y;
	update_balance(x);
	update_balance(y);
	x = y;
}

void form::big_right(Node*& node) {
	rotate_left(node->left);
	rotate_right(node);
}

void form::big_left(Node*& node) {
	rotate_right(node->right);
	rotate_left(node);
}