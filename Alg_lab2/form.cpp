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
	if (root == nullptr || root->num == key)
		return root;
	if (key > root->num)
		return search_node(root->right, key);
	return search_node(root->left, key);
}

Node* form::insert_node(Node* root, int num, Node* p) {
	if (root == nullptr) {
		Node* newnode = create_node(num);
		newnode->parent = p;
		return newnode;
	}
	if (num < root->num)
		root->left = insert_node(root->left, num, root);
	else
		root->right = insert_node(root->right, num, root);
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

	if (key < root->num) {
		root->left = delete_node(root->left, key);
		if (root->left != nullptr) {
			root->left->parent = root;
		}
	}
	else if (key > root->num) {
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
		root->num = tmp->num;
		root->right = delete_node(root->right, root->num);
		if (root->right != nullptr)
			root->right->parent = root;
	}
	return root;
}

void print_tree(Node* root, string space, bool left) {

	if (root != nullptr) {
		cout << space + "|--";

		cout << root->num;
		if (root->parent == nullptr) cout << " (root)\n";
		else cout << " (parent: " << root->parent->num << ")\n";

		print_tree(root->left, space + (left ? "|   " : "    "), true);
		print_tree(root->right, space + (left ? "|   " : "    "), false);

	}

}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int form::get_height(Node* root) {

	if (root == nullptr) return 0;

	return 1 + max(get_height(root->left),get_height(root->right));
}

void pre_order(Node* node) {
	if (node != nullptr) {
		cout << node->num << " -> ";
		pre_order(node->left);
		pre_order(node->right);

	}
}

void in_order(Node* node) {
	if (node != nullptr) {
		in_order(node->left);
		cout << node->num << " -> ";
		in_order(node->right);
	}
}

void post_order(Node* node) {
	if (node != nullptr) {
		post_order(node->left);
		post_order(node->right);
		cout << node->num << " -> ";
	}
}

void BFS(Node* node) {
	if (node != nullptr) {
		cout << node->num << " -> ";

	}
}

void DFS(Node* node) {
	if (node != nullptr) {

	}
}