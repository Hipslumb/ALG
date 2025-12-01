#include "Another.h"

void form::filltree(tree type) {
	int arr[10] = { 20, 10, 110, 100, 50, 55, 70, 40, 15, 5 };
	//int arr[10] = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35 };
	for (int i = 0; i < 10; i++) {
		insert(arr[i], type);
	}
}

void form::searchresult(int key) {
	Node* find = search_node(root, key);

	if (find != nullptr) {
		cout << "\nSearch result: " << find->key
			<< " (parent: " << (find->parent ? to_string(find->parent->key) : "null")
			<< ", left: " << (find->left ? to_string(find->left->key) : "null")
			<< ", right: " << (find->right ? to_string(find->right->key) : "null") << ")";
	}
	else {
		cout << "\nSearch result: null";
	}
}

void print_tree(Node* root, string space, bool left, tree tree) {

	if (root != nullptr) {
		cout << space + "|--";
		if (root->key == 0) cout << "nil\n";
		else {
			cout << root->key;
			if (root->parent == nullptr) cout << " (root";
			else { 
				cout << " (parent: "; 
				if (root->parent->key == 0) cout << "nil";
				else cout << root->parent->key;
			}

			if (tree == AVL) cout << ", b_f = " << root->balance_factor << ")\n";
			else if (tree == RB) {
				if (root->color == RED) cout << ", RED)\n";
				else cout << ", BLACK)\n";
			}
			else cout << ")\n";
		}

		print_tree(root->right, space + (left ? "|   " : "    "), true, tree);
		print_tree(root->left, space + (left ? "|   " : "    "), false, tree);

	}

}

int main() {
	form BT_tree(BT), AVL_tree(AVL), RB_tree(RB);
	BT_tree.BTtree();
	AVL_tree.AVLtree(); 
	RB_tree.RBtree();
	cout << "\nend process\n\n";
	return 0;
}