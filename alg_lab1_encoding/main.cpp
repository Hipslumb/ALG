#include "Huffman.h"

/*	"encoding/english.txt"
	"encoding/Antichnaya mifologiya.txt"
	"encoding/enwik7"
	"encoding/HWVEAudioSession.exe"
	"encoding/RGB.raw"
	"encoding/סונûי.raw"
	"encoding/׳ֱ.raw"*/

int main() {
	cout << "\n\n";
	clock_t start = clock();
	string infile = "encoding/HWVEAudioSession.exe";
	string outfile = "encoded/test.bin";
	string decodedfile = "decoded/test.bin";
	int orig_size = 0;
	LZW_compress(infile, orig_size, outfile);

	clock_t end = clock();
	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	cout << "\nTIME: " << time_taken << " seconds.";

	vector<uc> decoded = LZW_decompress(outfile);
	//save_data(decoded, decodedfile);
	cout << "\n";
	vector<uc> original = load_data(infile);
	if (orig_size == decoded.size()) {
		cout << "SAME SIZE\n";
		if (original == decoded) {
			cout << "SAME DATA\n";
			save_data(decoded, decodedfile);
		}
		else {
			cout << "WRONG DATA\n";
		}
	}
	else {
		cout << "WRONG SIZE\n";
	}
	

	cout << "\n\n";
	return 0;
}