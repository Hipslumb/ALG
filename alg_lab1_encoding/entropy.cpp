#include "functions.h"

double entropy(vector<unsigned char> text, int bytes) {
	
	int size = text.size() / bytes;
	map<string, int> sym;
	for (int i = 0;i < size;i++) {
		string element;
		for (int j = 0; j < bytes; j++) {
			element += text[i * bytes + j];
		}
		sym[element]++;
	}

	double H = 0; //-sum(pi*log2(pi)

	for (auto& s : sym) {
		double Pi = (double)s.second / size;
		H -= Pi * log2(Pi);
	}

	return H;
}

void func_H() {
	ifstream in("D:/Documents/Study/2 курс/АЛГ/encoding/Alice.txt", ios::binary);
	ofstream out("D:/Documents/Study/2 курс/АЛГ/encoding/english.txt", ios::binary);

	char cur;
	while (in.get(cur)) {
		if ((unsigned char)cur < 128) {
			out.put(cur);
		}
	}

	in.close(); out.close();
	const int max = 1024 * 1024;

	ifstream file("D:/Documents/Study/2 курс/АЛГ/encoding/english.txt", ios::binary | ios::ate);
	if (!file.is_open()) {
		cout << "Не могу открыть english.txt" << endl;
		return;
	}
	int size = file.tellg();

	file.seekg(0, ios::beg);
	vector<unsigned char> text(size);
	file.read(reinterpret_cast<char*>(text.data()), size);
	file.close();

	ofstream f("D:/Documents/Study/2 курс/АЛГ/encoding/entropy", ios::binary);

	for (int n = 1; n < 128; n++) {
		double H = entropy(text, n);
		f << n << " " << H << "\n";
	}

	f.close();
}