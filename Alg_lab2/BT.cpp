#include "Another.h"

void BTtree() {
	form tree;
	filltree(&tree, BT);

	cout << "\n////////////////BST:////////////////\n\n";
	print_tree(tree.root, "", true, BT);

	cout << "\nHeight: " << get_height(tree.root);
	cout << "\nMIN: " << tree.min_node(tree.root)->key;
	cout << "\nMAX: " << tree.max_node(tree.root)->key;

	cout << "\npre-order: "; pre_order(tree.root); cout << "end";
	cout << "\nin-order: "; in_order(tree.root); cout << "end";
	cout << "\npost-order: "; post_order(tree.root); cout << "end";
	cout << "\nBFS: "; BFS(tree.root); cout << "end";
	searchresult(tree, 100);
	tree.delete_n(20, BT);
	tree.delete_n(110, BT);

	cout << "\n\nafter delete:\n";
	print_tree(tree.root, "", true, BT);
}
