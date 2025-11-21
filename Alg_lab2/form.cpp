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
	return root;
}

void print_tree(Node* root, string space, bool left) {

	if (root != nullptr) {
		cout << space + "|--";

		cout << root->key;
		if (root->parent == nullptr) cout << " (root)\n";
		else cout << " (parent: " << root->parent->key << ")\n";

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
	form tree;
	int hight = tree.get_height(root);
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

void DFS(Node* root) {
	if (root != nullptr) {
		Node* cur = root;
		Node* prev = nullptr;
		Node* next = nullptr;
		while (cur != nullptr) {
			if (prev == cur->parent) {
				cout << cur->key << " -> ";
				if (cur->left != nullptr)
					next = cur->left;
				else if (cur->right != nullptr)
					next = cur->right;
				else
					next = cur->parent;
			}
			else if (prev == cur->left) {
				if (cur->right != nullptr)
					next = cur->right;
				else
					next = cur->parent;
			}
			else
				next = cur->parent;
			prev = cur;
			cur = next;
		}
	}
}