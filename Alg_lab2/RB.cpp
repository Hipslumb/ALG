#include "Another.h"

void form::RBtree() {
	filltree(RB);

	cout << "\n////////////////RnB:////////////////\n\n";
	print_tree(root, "", true, RB);
	searchresult(100);
	cout << "\nBH = " << blackHight(root);

	
	deleteRB(55);
	deleteRB(110);
	

	cout << "\n\nafter delete:\n";
	print_tree(root, "", true, RB);

	cout << "\nBH = " << blackHight(root);
}