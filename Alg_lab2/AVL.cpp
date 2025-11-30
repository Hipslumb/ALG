#include "Another.h"

void form::AVLtree() {
	filltree(AVL);
	cout << "\n\n////////////////AVL:////////////////\n\n";
	print_tree(root, "", true, AVL);

	searchresult(100);

	delete_n(20, AVL);
	delete_n(110, AVL);

	delete_n(6, AVL);

	cout << "\n\nafter delete:\n";
	print_tree(root, "", true, AVL);
}