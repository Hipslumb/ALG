#include "Another.h"

int main() {
	form tree;
	tree.insert(50);
	tree.insert(30);
	tree.insert(20);
	tree.insert(10);
	tree.insert(100);
	tree.insert(60);
	tree.insert(110);
	tree.insert(70);

	cout << "BST:\n";
	print_tree(tree.root, "", true);

	cout << "AVL:\n";
	tree.balancing(tree.root);
	print_tree(tree.root, "", true);


	cout << "\nHeight: " << get_height(tree.root);
	cout << "\nMIN: " << tree.min_node(tree.root)->key;
	cout << "\nMAX: " << tree.max_node(tree.root)->key;

	Node* find = tree.search_node(tree.root,30);

	if (find != nullptr) {
		cout << "\nSearch result: " << find->key
			<< " (parent: " << (find->parent ? to_string(find->parent->key) : "null")
			<< ", left: " << (find->left ? to_string(find->left->key) : "null")
			<< ", right: " << (find->right ? to_string(find->right->key) : "null") << ")";
	}
	else {
		cout << "\nSearch result: null";
	}

	cout << "\npre-order: "; pre_order(tree.root); cout << "end";
	cout << "\nin-order: "; in_order(tree.root); cout << "end";
	cout << "\npost-order: "; post_order(tree.root); cout << "end";

	cout << "\nBFS: "; BFS(tree.root); cout << "end";

	tree.delete_n(20);
	tree.delete_n(110);

	cout << "\n\nBST after delete:\n";
	print_tree(tree.root, "", true);

	cout << "\n\nafter balancing:\n";
	tree.balancing(tree.root);
	print_tree(tree.root, "", true);

	
	cout << "\n\n";
	return 0;
}