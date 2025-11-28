#include "Another.h"

int form::count_balance(Node* node) {
	if (node == nullptr) return 0;
	int height_left = get_height(node->left);
	int height_right = get_height(node->right);

	return height_left - height_right;
}

void form::update_balance(Node* node) {
	while (node != nullptr) {
		node->balance_factor = count_balance(node);
		node = node->parent;
	}
}

void form::balancing(Node*& node, tree tree) {
	if (node == nullptr) return;
    balancing(node->left, tree);
    balancing(node->right, tree);

	if (node->balance_factor > 1 && node->left != nullptr) {
		if (node->left->balance_factor >= 0) rotate_right(node,tree);
		else big_right(node, tree);
	}
	else if (node->balance_factor < -1 && node->right != nullptr) {
		if (node->right->balance_factor <= 0) rotate_left(node,tree);
		else big_left(node, tree);
	}

    update_balance(node);
}
void form::rotate_right(Node*& x, tree tree) {
    if (x->left == nullptr) return;
    Node* y = x->left;
    x->left = y->right;
    y->right = x;

    if (x->left != nullptr) x->left->parent = x;

    y->parent = x->parent;
    x->parent = y;

    if (y->parent != nullptr) {
        if (y->parent->left == x) y->parent->left = y;
        else y->parent->right = y;
    }

    if (AVL) {
        update_balance(x);
        update_balance(y);
    }

    x = y;
}

void form::rotate_left(Node*& x, tree tree) {
    if (x->right == nullptr) return;
    Node* y = x->right;
    x->right = y->left;
    y->left = x;

    if (x->right != nullptr) x->right->parent = x;

    y->parent = x->parent;
    x->parent = y;

    if (y->parent != nullptr) {
        if (y->parent->left == x) y->parent->left = y;
        else y->parent->right = y;
    }

    if (tree == AVL) {
        update_balance(x);
        update_balance(y);
    }

    x = y;
}
void form::big_right(Node*& node, tree tree) {
	rotate_left(node->left,tree);
	rotate_right(node,tree);
}

void form::big_left(Node*& node, tree tree) {
	rotate_right(node->right,tree);
	rotate_left(node,tree);
}