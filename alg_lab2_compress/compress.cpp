#include "fun.h"
#include "table.h"

void Image::compressor(string outfile, int quality) {
    //1
	to_YCbCr();
    int w = width, h = height;

    vector<uc> Y(w * h);
    vector<uc> Cb(w * h);
    vector<uc> Cr(w * h);

    for (int i = 0; i < w * h; i++) {
        Y[i] = data[i * 3];
        Cb[i] = data[i * 3 + 1];
        Cr[i] = data[i * 3 + 2];
    }
    int k = 2; int N = 8, M = 8;
    //1.2 for Cb, Cr
    vector<uc> Cb_down = downsampling(Cb, w, h, k);
    vector<uc> Cr_down = downsampling(Cr, w, h, k);

    int Y_table[64], C_table[64];
    new_table(Y_QT,quality,Y_table);
    vector<uc> Y_compressed = compress(Y, w, h, Y_table);

    new_table(CbCr_QT, quality, C_table);
    vector<uc> Cb_compressed = compress(Cb_down, w / k, h / k, C_table);
    vector<uc> Cr_compressed = compress(Cr_down, w / k, h / k, C_table);

    saveDATA(outfile, Y_compressed, Cb_compressed, Cr_compressed, quality);
}

vector<uc> compress(const vector<uc>& channel, int w, int h, const int q_table[64]) {
    vector<uc> compressed;
    vector<vector<vector<double>>> blocks = split_blocks(channel, w, h, 8, 8);
    vector<int> allDC;
    vector<AC> RLE;

    for (auto& block : blocks) {
        //2
        vector<vector<double>> dct = DCT_bymatrix(block, 1);
        
        vector<vector<int>> quant = quantize(dct, q_table);

        vector<int> zigzagged = zigzag(quant);
        allDC.push_back(zigzagged[0]);
        
        vector<int> ac(zigzagged.begin() + 1, zigzagged.end());
        //2.2
        vector<AC> rle = rle_encoding(ac, 8, 8);
        RLE.insert(RLE.end(), rle.begin(), rle.end());
    }
    //2.1
    vector<int> diffs = encodeDC(allDC);
    vector<DC> dc = vlc_encoding(diffs);
    //3
    vector<uc> dcEncoded = Huf_encodingDC(dc, dc_Huffman);
    vector<uc> acEncoded = Huf_encodingAC(RLE, ac_Huffman);

    compressed.insert(compressed.end(), dcEncoded.begin(), dcEncoded.end());
    compressed.insert(compressed.end(), acEncoded.begin(), acEncoded.end());

    return compressed;
}
