#include "Node.h"

void form::delete_tree(Node* node) {
	if (node != nullptr) {
		delete_tree(node->left);
		delete_tree(node->right);
		delete node;
	}
}
Node* form::create_node(int num) {
	return new Node(num);
}

Node* form::search_node(Node* root, int key) {
	if (root == nullptr || root->key == key)
		return root;
	if (key > root->key)
		return search_node(root->right, key);
	return search_node(root->left, key);
}

Node* form::insert_node(Node* root, int num, Node* p) {
	if (root == nullptr) {
		Node* newnode = create_node(num);
		newnode->parent = p;
		return newnode;
	}
	if (num < root->key)
		root->left = insert_node(root->left, num, root);
	else
		root->right = insert_node(root->right, num, root);
	root->balance_factor = count_balance(root);
	return root;
}

Node* form::min_node(Node* root) {
	Node* cur = root;
	while (cur && cur->left != nullptr)
		cur = cur->left;
	return cur;
}
Node* form::max_node(Node* root) {
	Node* cur = root;
	while (cur && cur->right != nullptr)
		cur = cur->right;
	return cur;
}


Node* form::delete_node(Node* root, int key) {
	if (root == nullptr) return root;

	if (key < root->key) {
		root->left = delete_node(root->left, key);
		if (root->left != nullptr) {
			root->left->parent = root;
		}
	}
	else if (key > root->key) {
		root->right = delete_node(root->right, key);
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
		root->right = delete_node(root->right, root->key);
		if (root->right != nullptr)
			root->right->parent = root;
	}
	
	balancing(root);
	return root;
}



