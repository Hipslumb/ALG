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

void form::change_node(Node* x, Node* y) {
	if (x->parent == psevdo)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	if (y != psevdo)
		y->parent = x->parent;
}
int form::blackHight(Node* node) {
	if (node == psevdo) return 1;
	int left = blackHight(node->left);
	int right = blackHight(node->right);
	if (left != right) { 
		cout << "\nWhong BH in " << node->key; 
		return max(left, right);
	}
	if (node->color == BLACK) return 1 + left;
	return left;
}

void form::deleteRB(int key) {
	Node* node = search_node(root, key);
	if (node == nullptr || node == psevdo) return;

	if (node->left == psevdo && node->right == psevdo) {
		if (node == root) {
			delete root;
			root = psevdo;
		}
		else {
			Node* parent = node->parent;
			bool left = node == parent->left;


			if (left) {
				parent->left = psevdo;
			}
			else parent->right = psevdo;

			if (node->color == BLACK) {
				Node* tmp = new Node(-1);
				tmp->parent = parent;
				tmp->color = BLACK;
				tmp->left = psevdo;
				tmp->right = psevdo;
				if (left) {
					parent->left = tmp;
				}
				else parent->right = tmp;
				delete node;
				fix_delete(tmp);
				if (left) {
					parent->left = psevdo;
				}
				else parent->right = psevdo;
				delete tmp;
			}
			else delete node;
		}
		return;
	}

	if (node->left != psevdo && node->right == psevdo) {
		Node* child = node->left;
		change_node(node, child);

		if (node->color == BLACK) 
			fix_delete(child);
		
		delete node;
	}
	else if (node->right != psevdo && node->left == psevdo) {
		Node* child = node->right;
		change_node(node, child);
		if (node->color == BLACK) 
			fix_delete(child);
		
		delete node;
	}
	else {
		Node* min = min_node(node->right);
		color node_color = node->color;
		color min_color = min->color;

		int min_key = min->key;
		deleteRB(min_key);
		node->key = min_key;
		node->color = node_color;

		if (min_color == BLACK) {
			fix_delete(node);
		}
	}
}
void form::fix_delete(Node* x) {
	
	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			
			Node* bro = x->parent->right;
			if (bro == psevdo) break;
			//1
			if (bro->color == RED) {
				bro->color = BLACK;
				x->parent->color = RED;
				rotate_leftRB(x->parent);
				bro = x->parent->right;
			}
			//2
			if (bro->left->color == BLACK && bro->right->color == BLACK) {
				bro->color = RED;
				x = x->parent;
			}
			else {
				//3
				if (bro->right->color == BLACK) {
					bro->left->color = BLACK;
					bro->color = RED;
					rotate_rightRB(bro);
					bro = x->parent->right;
				}
				//4
				bro->color = x->parent->color;
				x->parent->color = BLACK;
				bro->right->color = BLACK;
				rotate_leftRB(x->parent);
				x = root;
			}

		}
		else {
			Node* bro = x->parent->left;
			if (bro == psevdo) break;
			//1
			if (bro->color == RED) {
				bro->color = BLACK;
				x->parent->color = RED;
				rotate_rightRB(x->parent);
				bro = x->parent->left;
			}
			//2
			if (bro->left->color == BLACK && bro->right->color == BLACK) {
				bro->color = RED;
				x = x->parent;
			}
			else {
				//3
				if (bro->left->color == BLACK) {
					bro->right->color = BLACK;
					bro->color = RED;
					rotate_leftRB(bro);
					bro = x->parent->left;
				}
				//4
				bro->color = x->parent->color;
				x->parent->color = BLACK;
				bro->left->color = BLACK;
				rotate_rightRB(x->parent);
				x = root;
			}
		}

	}
	x->color = BLACK;
}
