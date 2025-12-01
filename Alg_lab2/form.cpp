#include "Node.h"

void form::delete_tree(Node* node) {
	if (node != nullptr && node != psevdo) {
		delete_tree(node->left);
		delete_tree(node->right);
		delete node;
	}
}
Node* form::create_node(int num) {
	return new Node(num);
}

Node* form::search_node(Node* root, int key) {
	if (root == nullptr || root == psevdo || root->key == key)
		return root;
	if (key > root->key)
		return search_node(root->right, key);
	return search_node(root->left, key);
}

Node* form::insertAVLorBT(Node* root, int key, Node* p, tree tree) {
	if (root == nullptr) {
		Node* newnode = create_node(key);
		newnode->parent = p;
		return newnode;
	}
	if (key == root->key) {
		return root;
	}
	if (key < root->key)
		root->left = insertAVLorBT(root->left, key, root, tree);
	else
		root->right = insertAVLorBT(root->right, key, root, tree);
	//for AVL
	if (tree == AVL) {
		root->balance_factor = count_balance(root);
		balancing(root, tree);
	}
	return root;
}

Node* form::min_node(Node* root) {
	if (root == nullptr) return nullptr;
	if (root == psevdo) return psevdo;
	Node* cur = root;
	while (cur->left != psevdo && cur->left != nullptr)
		cur = cur->left;
	return cur;
}
Node* form::max_node(Node* root) {
	if (root == nullptr) return nullptr;
	if (root == psevdo) return psevdo;
	Node* cur = root;
	while (cur->right != psevdo && cur->right != nullptr)
		cur = cur->right;
	return cur;
}

Node* form::delete_node(Node* root, int key, tree tree) {
	if (root == nullptr) return root;

	if (key < root->key) {
		root->left = delete_node(root->left, key, tree);
		if (root->left != nullptr) {
			root->left->parent = root;
		}
	}
	else if (key > root->key) {
		root->right = delete_node(root->right, key, tree);
		if (root->right != nullptr) {
			root->right->parent = root;
		}
	}
	else {
		Node* tmp = nullptr;
		if (root->left == nullptr || root->right == nullptr) {
			if (root->left == nullptr)
				tmp = root->right;
			else if (root->right == nullptr)
				tmp = root->left;

			if (tmp != nullptr)
				tmp->parent = root->parent;
			delete root;
			return tmp;
		}
		tmp = min_node(root->right);
		root->key = tmp->key;
		root->right = delete_node(root->right, root->key, tree);
		if (root->right != nullptr)
			root->right->parent = root;
	}
	//for AVL
	if (tree == AVL) {
		root->balance_factor = count_balance(root);
		balancing(root, tree);
	}
	return root;
}



