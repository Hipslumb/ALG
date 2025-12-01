#include "Another.h"

void form::RBtree() {
	filltree(RB);

	cout << "\n////////////////RnB:////////////////\n\n";
	print_tree(root, "", true, RB);
	searchresult(100);
	cout << "\nBH = " << blackHight(root);
	int arr[10] = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35 };

	
	deleteRB(55);
	deleteRB(110);
	

	cout << "\n\nafter delete:\n";
	print_tree(root, "", true, RB);

	cout << "\nBH = " << blackHight(root);
}