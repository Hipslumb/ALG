#include "Another.h"
#include <random>
#include <unordered_set>

void experiment(tree type) {
	fstream file;
	if (type == BT)
		file.open("4_task.txt", std::ios::out);
	else if (type == AVL)
		file.open("5.1_task.txt", std::ios::out);
	else
		file.open("5.2_task.txt", std::ios::out);
	form tree(type);
	int n = 0, prev_h = 0;

	std::mt19937 generate(std::random_device{}());
	std::uniform_int_distribution<int> dist(-10000000, 10000000);
	std::unordered_set<int> used_keys;
	used_keys.reserve(40000);
	
	while (n < 5000) {
		int key = dist(generate);
		if (used_keys.insert(key).second) {
			tree.insert(key, type);
			n++;

			int h = get_height(tree.root, tree.psevdo);
			if (1) { //h != prev_h
				file << n << " " << h << "\n";
				prev_h = h;
			}
		}
	}
	file.close();
}

void monoton_experiment(tree type) {
	fstream file;
	if (type == AVL)
		file.open("6.1_task.txt", std::ios::out);
	else
		file.open("6.2_task.txt", std::ios::out);
	form tree(type);
	int n = 1, prev_h = 0;
	while (n < 10000) {
		int key = n + 7;
		tree.insert(key, type);
		int h = get_height(tree.root, tree.psevdo);
		if (1) { //h != prev_h
			file << n << " " << h << "\n";
		}
		prev_h = h;
		n++;
	}
	file.close();
}