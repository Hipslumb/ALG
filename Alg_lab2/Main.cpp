#include "Node.h"

int main() {
	form tree; Node* root = nullptr;
	root = tree.insert_node(root, 50, nullptr);
	root = tree.insert_node(root, 30, nullptr);
	root = tree.insert_node(root, 20, nullptr);
	root = tree.insert_node(root, 10, nullptr);
	root = tree.insert_node(root, 100, nullptr);
	root = tree.insert_node(root, 60, nullptr);
	root = tree.insert_node(root, 110, nullptr);
	root = tree.insert_node(root, 70, nullptr);

	cout << "BST:\n";
	print_tree(root, "", true);

	cout << "\nHeight: " << tree.get_height(root);

	cout << "\nMIN: " << tree.min_node(root)->num;
	cout << "\nMAX: " << tree.max_node(root)->num;

	cout << "\npre-order: "; pre_order(root); cout << "end";

	cout << "\nin-order: "; in_order(root); cout << "end";

	cout << "\npost-order: "; post_order(root); cout << "end";

	root = tree.delete_node(root, 20);
	root = tree.delete_node(root, 110);

	cout << "\n\nBST after delete:\n";
	print_tree(root, "", true);
	cout << "\n\n";
	return 0;
}