#define STB_IMAGE_IMPLEMENTATION
#include "functions.h"

void from9_to7() {
	//here i made enwik7 from enwik9 (cutting file)
	ifstream in("encoding/enwik9", ios::binary);
	ofstream out("encoding/enwik7", ios::binary);
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

void save_data(vector<uc> data, string file) {
	ofstream out(file, ios::binary);
	out.write((char*)data.data(), data.size());
	out.close();
}

void packing(vector<uc>& out, int integer, int bytes) {
	for (int i = 0; i < bytes; i++) {
		out.push_back(static_cast<uc>(integer & 0xff));
		integer >>= 8;
	}
}
void unpacking(vector<uc> in, int& integer, int bytes, int& pos) {

	for (int i = 0; i < bytes; i++) {
		integer |= (in[pos + i] << (8 * i));
	}
	pos += bytes;
}

void compare(const char* name, const char* enname) {
	ifstream orig(name, ios::binary | ios::ate);
	ifstream en(enname, ios::binary | ios::ate);

	int orig_size = orig.tellg();
	int en_size = en.tellg();

	orig.close(); en.close();

	cout << "k = " << double(orig_size) / (en_size) << "\n";

}

void create_raw() {
	const char* original = "encoding/ва.png";
	Image img;

	const char* raw = "encoding/ва.raw";

	if (img.load(original)) {
		img.save(raw);
		//printHEX(raw, 1000, 0);
	}
}