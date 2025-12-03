#include "Another.h"


int max(int a, int b) {
	return (a > b) ? a : b;
}

int get_height(Node* root, Node* psevdo) {

	if (root == nullptr || root == psevdo) return 0;

	return 1 + max(get_height(root->left, psevdo), get_height(root->right, psevdo));
}

void pre_order(Node* root) {
	if (root != nullptr) {
		cout << root->key << " -> ";
		pre_order(root->left);
		pre_order(root->right);

	}
}
void in_order(Node* root) {
	if (root != nullptr) {
		in_order(root->left);
		cout << root->key << " -> ";
		in_order(root->right);
	}
}
void post_order(Node* root) {
	if (root != nullptr) {
		post_order(root->left);
		post_order(root->right);
		cout << root->key << " -> ";
	}
}

void BFS(Node* root) {
	int hight = get_height(root, nullptr);
	for (int l = 0;l < hight;l++) {
		print_l(root, l);
	}
}
void print_l(Node* node, int l) {
	if (node != nullptr) {
		if (l == 0) {
			cout << node->key << " -> ";
		}
		else {
			print_l(node->left, l - 1);
			print_l(node->right, l - 1);
		}
	}
}

