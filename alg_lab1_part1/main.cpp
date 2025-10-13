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



void by_selection(int size, int* array) {
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

void merge(int* array, int left, int right) {

	//fr ex 1 3 2 4 5 //

	unsigned mid = left + (right - left) / 2, i = left, j = mid + 1, k = 0; int tmp[1000];

	while (i <= mid && j <= right) {
		if (array[i] <= array[j]) {
			tmp[k] = array[i];i++;
		}
		else {
			tmp[k] = array[j];j++;
		}
		k++;
	}

	while (i <= mid) {
		tmp[k] = array[i]; i++; k++;
	}
	while (j <= right) {
		tmp[k] = array[j]; j++; k++;
	}
	for (i = 0; i < k; i++) array[left + i] = tmp[i];
}

void by_merge(int* array, int left, int right) {

	//fr ex 1 3 2 4 5 // 

	if (left < right) {
		if (right - left == 1) {
			if (array[left] > array[right]) {
				swap(array, left, right);
			}
		}
		else {
			by_merge(array, left, left + (right - left) / 2);
			by_merge(array, left + (right - left) / 2 + 1, right);
			merge(array, left, right);
		}
	}
		
}


void by_heap(int size, int* array) {

}


int main() {
	setlocale(LC_ALL, "RU");
	fstream in; in.open("input.txt",ios::in);
	
	int size = countsize(in);
	int* array = new int[size];
	array_create(in, size, array);

	unsigned c;
	cout << "\nSelect the sorting algorithm (1 - insertion, 2 - selection, 3 - merge, 4 - heap): ";
	cin >> c; unsigned left = 0, right = size - 1;
	switch (c) {
	case 1:
		by_insertion(size, array);break;
	case 2:
		by_selection(size, array); break;
	case 3:
		by_merge(array, left, right);break;
	case 4: 
		break;
	default: 
		cout << "There is no such algorithm.";
	}
	cout << "Sorted array: "; output(size, array);

	in.close();
	cout << "\n\nCOMPLETED.\n";
	return 0;
}

