#include "Another.h"

void form::RBtree() {
	filltree(RB);

	cout << "\n////////////////RnB:////////////////\n\n";
	print_tree(root, "", true, RB);
	searchresult(100);

	/*tree.delete_n(5, RB);
	tree.delete_n(55, RB);

	cout << "\n\nafter delete:\n";
	print_tree(tree.root, "", true, RB);*/
}