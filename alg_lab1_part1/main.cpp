#include <fstream>
#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::fstream;
using std::ios;

int countsize(fstream& f) {
	int size = 0; int tmp = 0;
	while (f >> tmp) {
		size++;
	}
	f.clear();
	f.seekg(0);
	return size;
}
void array_create(fstream& f, int size, int* array) {
	cout << "The original array: ";
	for (unsigned i = 0;i < size;i++) {
		f >> array[i];
		cout << array[i] << " ";
	}
}
void output(int size, int* array) {
	for (unsigned i = 0;i < size;i++) {
		cout << array[i] << " ";
	}
}
void swap(int* array, unsigned i, unsigned j) {
	unsigned tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}



void by_choice(int size, int* array) {
	unsigned i, j, min;
	for (i = 0;i < size - 1;i++) {
		min = i;
		for (j = i + 1;j < size;j++) {
			if (array[j] < array[min]) min = j;
		}
		swap(array, i, min);
	}
}

void by_insertion(int size,int* array) {
	int i, j, cur;
	for (i = 1;i < size;i++) {
		cur = array[i];
		for (j = i - 1;j >= 0 && cur < array[j];j--) {
			array[j + 1] = array[j];
		}
		array[j + 1] = cur;
	}
}

void main() {
	setlocale(LC_ALL, "RU");
	fstream in; in.open("input.txt",ios::in);
	
	int size = countsize(in);
	int* array = new int[size];
	array_create(in, size, array);

	bool x;
	cout << "\nÂÛÁÎÐ ÌÅÒÎÄÀ ÑÎÐÒÈÐÎÂÊÈ (1 - âûáîðîì,0 - âñòàâêîé): ";
	cin >> x;
	switch (x) {
	case 1:
		by_choice(size, array); break;
	case 0:
		by_insertion(size, array);
	}
	cout << "Sorted array: "; output(size, array);

	in.close();
	cout << "\n\nÐàáîòà ñ ïðîãðàììîé çàâåðøåíà\n";
}

