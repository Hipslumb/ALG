#include "functions.h"

void from9_to7() {
	//here i made enwik7 from enwik9 (cutting file)
	ifstream in("D:/Documents/Study/2 êóðñ/ÀËÃ/encoding/enwik9", ios::binary);
	ofstream out("D:/Documents/Study/2 êóðñ/ÀËÃ/encoding/enwik7", ios::binary);
	long long size7 = 10000000;
	static char buf[1024 * 1024];
	while (size7 > 0) {
		int size9 = (size7 > sizeof(buf)) ? sizeof(buf) : size7;
		in.read(buf, size9);
		out.write(buf, in.gcount());
		size7 -= in.gcount();
	}
}

void HEX(unsigned char a) {
	cout << "0x" << setw(2) << setfill('0') << hex << (int)a << " ";
}

void printHEX(const char* name, int max, bool text) {
	ifstream file(name, ios::binary);
	unsigned char byte;
	int k = 0;
	while (file.read((char*)&byte, 1) && k < max) {
		HEX(byte);
		if (!text)
			if (k == 3 || k == 7 || k == 8 || k == 9) cout << "\n";
		k++;
	}
	cout << "\n";
}
