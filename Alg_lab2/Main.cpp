#include "Another.h"

void filltree(form* this_tree, tree type) {
	int arr[10] = { 20, 10, 110, 100, 50, 55, 70, 40, 15, 5 };
	for (int i = 0; i < 10; i++) {
		this_tree->insert(arr[i], type);
	}
}

void searchresult(form& tree, int key) {
	Node* find = tree.search_node(tree.root, key);

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

		cout << root->key;
		if (root->parent == nullptr) cout << " (root";
		else cout << " (parent: " << root->parent->key;

		if (tree == AVL) cout << ", b_f = " << root->balance_factor << ")\n";
		else if (tree == RB) {
			if (root->color == RED) cout << ", color = RED)\n";
			else cout << ", color = BLACK)\n";
		}
		else cout << ")\n";

		print_tree(root->left, space + (left ? "|   " : "    "), true, tree);
		print_tree(root->right, space + (left ? "|   " : "    "), false, tree);

	}

}

int main() {
	BTtree(); AVLtree(); //RBtree();
	cout << "\n\n";
	return 0;
}