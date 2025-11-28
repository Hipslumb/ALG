#include "Another.h"

void AVLtree() {
	form tree;
	filltree(&tree, AVL);
	cout << "\n\n////////////////AVL:////////////////\n\n";
	print_tree(tree.root, "", true, AVL);

	searchresult(tree, 100);

	tree.delete_n(20, AVL);
	tree.delete_n(110, AVL);

	cout << "\n\nafter delete:\n";
	print_tree(tree.root, "", true, AVL);
}