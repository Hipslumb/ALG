#include "Another.h"

Node* form::insertRB(int key) {
	Node* current = root;
	Node* parent = psevdo;
	while (current != psevdo) {
		parent = current;
		if (key < current->key) {
			current = current->left;
		}
		else if (key > current->key) {
			current = current->right;
		}
		else {
			return root;
		}
	}
	Node* newNode = new Node(key);
	newNode->parent = parent;
	newNode->left = psevdo;
	newNode->right = psevdo;
	newNode->color = RED;
	if (parent != psevdo) {
		if (key < parent->key)
			parent->left = newNode;
		else
			parent->right = newNode;
	}
	if (root == psevdo) {
		root = newNode;
	}
	fix_tree(newNode);
	return root;
}

void form::fix_tree(Node* node) {
	while (node != root && node->parent != psevdo && node->parent->color == RED) {
		Node* parent = node->parent;
		Node* grand = parent->parent;
		if (grand == psevdo) break;

		Node* uncle = (parent == grand->left) ? grand->right : grand->left;
		if (uncle != psevdo && uncle->color == RED) {
			parent->color = BLACK;
			uncle->color = BLACK;
			grand->color = RED;

			node = grand;
		}
		else {
			if ((parent == grand->left && node == parent->right) ||
				(parent == grand->right && node == parent->left)) {
				if (node == parent->right && parent == grand->left) {
					rotate_leftRB(parent);
					node = parent;
					parent = node->parent;
				}
				else if (node == parent->left && parent == grand->right) {
					rotate_rightRB(parent);
					node = parent;
					parent = node->parent;
				}
			}
			grand = parent->parent;
			if (grand == psevdo) break;

			parent->color = BLACK;
			grand->color = RED;

			if (parent == grand->left)
				rotate_rightRB(grand);
			else
				rotate_leftRB(grand);
			break;
		}
	}
	root->color = BLACK;
}

void form::rotate_rightRB(Node* x) {
	if (x == psevdo || x->left == psevdo) return;

	Node* y = x->left;
	x->left = y->right;

	if (y->right != psevdo) {
		y->right->parent = x;
	}

	y->parent = x->parent;

	if (x->parent != psevdo) {
		if (x->parent->left == x) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
	}

	y->right = x;
	x->parent = y;
	if (y->parent == psevdo) {
		root = y;
	}
}
void form::rotate_leftRB(Node* x) {
	if (x == psevdo || x->right == psevdo) return;

	Node* y = x->right;
	x->right = y->left;

	if (y->left != psevdo) {
		y->left->parent = x;
	}

	y->parent = x->parent;

	if (x->parent != psevdo) {
		if (x->parent->right == x) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
	}

	y->left = x;
	x->parent = y;
	if (y->parent == psevdo) {
		root = y;
	}
}

void form::deleteRB(int key) {
	Node* node = search_node(root, key);
	if (node->color == RED && node->left == psevdo && node->right == psevdo) {
		if (node->parent == psevdo);
		else {
			Node* side = (node == node->parent->left) ? node->parent->left : node->parent->right;
			side = psevdo;
		}
		delete node;
		return;
	}
	if ((node->right->color == RED || node->left->color == RED)
		&& (node->left == psevdo || node->right == psevdo)) {
		Node* child = (node->left != psevdo) ? node->left : node->right;
		child->parent = node->parent;
		if (node->parent == psevdo);
		else {
			if (node == node->parent->left) node->parent->left = child;
			else node->parent->right = child;
		}
		delete node;
		return;
	}

	
}