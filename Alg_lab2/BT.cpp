#include "Another.h"

void form::BTtree() {
	filltree(BT);

	cout << "\n////////////////BST:////////////////\n\n";
	print_tree(root, "", true, BT);

	cout << "\nHeight: " << get_height(root, nullptr);
	cout << "\nMIN: " << min_node(root)->key;
	cout << "\nMAX: " << max_node(root)->key;

	cout << "\npre-order: "; pre_order(root); cout << "end";
	cout << "\nin-order: "; in_order(root); cout << "end";
	cout << "\npost-order: "; post_order(root); cout << "end";
	cout << "\nBFS: "; BFS(root); cout << "end";
	searchresult(100);
	delete_n(20, BT);
	delete_n(110, BT);

	cout << "\n\nafter delete:\n";
	print_tree(root, "", true, BT);
}
