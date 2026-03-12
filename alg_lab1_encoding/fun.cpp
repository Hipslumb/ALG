#define STB_IMAGE_IMPLEMENTATION
#include "functions.h"

void from9_to7() {
	//here i made enwik7 from enwik9 (cutting file)
	ifstream in((string)mf + "enwik9", ios::binary);
	ofstream out((string)mf + "enwik7", ios::binary);
	long long size7 = 10000000;
	static char buf[1024 * 1024];
	while (size7 > 0) {
		int size9 = (size7 > sizeof(buf)) ? sizeof(buf) : size7;
		in.read(buf, size9);
		out.write(buf, in.gcount());
		size7 -= in.gcount();
	}
}

void HEX(uc a) {
	cout << "0x" << setw(2) << setfill('0') << hex << (int)a << " ";
}

void printHEX(const char*  name, int max, bool text) {
	ifstream file(name, ios::binary);
	uc byte;
	int k = 0;
	while (file.read((char*)&byte, 1) && k < max) {
		HEX(byte);
		if (!text)
			if (k == 3 || k == 7 || k == 8 || k == 9) cout << "\n";
		k++;
	}
	cout << "\n";
}

vector<uc> load_data(string file) {
	ifstream in(file, ios::binary);
	vector<uc> data; char sym;
	while (in.get(sym)) {
		data.push_back((uc)sym);
	}
	in.close();
	return data;
}