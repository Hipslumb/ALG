#include "fun.h"
#include "table.h"

void dopFILL(vector<uc>& channel, int& w, int& h) {
    int new_w = ((w + 7) / 8) * 8;
    int new_h = ((h + 7) / 8) * 8;

    if (new_w == w && new_h == h) return;

    vector<uc> new_channel(new_w * new_h, 0);

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            new_channel[y * new_w + x] = channel[y * w + x];
        }
    }

    for (int by = 0; by < (new_h + 7) / 8; by++) {
        for (int bx = 0; bx < (new_w + 7) / 8; bx++) {
            int start_y = by * 8;
            int start_x = bx * 8;

            if (start_x + 8 <= w && start_y + 8 <= h) continue;

            int sum = 0;
            int count = 0;
            for (int y = start_y; y < min(start_y + 8, h); y++) {
                for (int x = start_x; x < min(start_x + 8, w); x++) {
                    sum += channel[y * w + x];
                    count++;
                }
            }
            int avg = (count > 0) ? sum / count : 128;

            for (int y = start_y; y < start_y + 8; y++) {
                for (int x = start_x; x < start_x + 8; x++) {
                    if (y >= h || x >= w) {
                        new_channel[y * new_w + x] = avg;
                    }
                }
            }
        }
    }

    channel = move(new_channel);
    w = new_w;
    h = new_h;
}

vector<uc> compress(const vector<uc>& channel, int w, int h, const int q_table[64], int& dc_len, bool is_Y) {
    vector<uc> compressed;
    vector<vector<vector<double>>> blocks = split_blocks(channel, w, h, 8, 8);
    vector<int> allDC;
    vector<AC> ac_rle;

    for (auto& block : blocks) {
        //2
        vector<vector<double>> dct = DCT_bymatrix(block, 1);

        vector<vector<int>> quant = quantize(dct, q_table);

        vector<int> zigzagged = zigzag(quant);
        allDC.push_back(zigzagged[0]);

        vector<int> ac(zigzagged.begin() + 1, zigzagged.end());
        //2.2
        vector<AC> rle = rle_encoding(ac, 8, 8);
        ac_rle.insert(ac_rle.end(), rle.begin(), rle.end());
    }
    //2.1
    vector<int> diffs = encodeDC(allDC);
    vector<DC> dc_vlc = vlc_encoding(diffs);
    //3
    vector<uc> dc_encoded = Huf_encodingDC(dc_vlc, dc_Huffman);

    map<int, string> ac_haff = (is_Y) ? AC_Y : AC_C;
    vector<uc> ac_encoded = Huf_encodingAC(ac_rle, ac_haff);

    dc_len = dc_encoded.size();

    compressed.insert(compressed.end(), dc_encoded.begin(), dc_encoded.end());
    compressed.insert(compressed.end(), ac_encoded.begin(), ac_encoded.end());

    return compressed;
}

void Image::compressor(string outfile, int quality) {
    //1
	to_YCbCr();
    orig_h = height; orig_w = width;
    int w = width, h = height; int dc_y, dc_cb, dc_cr;

    vector<uc> Y(w * h);
    vector<uc> Cb(w * h);
    vector<uc> Cr(w * h);

    for (int i = 0; i < w * h; i++) {
        Y[i] = data[i * 3];
        Cb[i] = data[i * 3 + 1];
        Cr[i] = data[i * 3 + 2];
    }
    dopFILL(Y, w, h);
    dopFILL(Cb, w, h);
    dopFILL(Cr, w, h);
    width = w;
    height = h;
    data_size = w * h * 3;

    int k = 2; int N = 8, M = 8;
    //1.2 for Cb, Cr
    vector<uc> Cb_down = downsampling(Cb, w, h, k);
    vector<uc> Cr_down = downsampling(Cr, w, h, k);

    int Y_table[64], C_table[64];
    new_table(Y_QT,quality,Y_table);
    vector<uc> Y_compressed = compress(Y, w, h, Y_table, dc_y, 1);

    new_table(CbCr_QT, quality, C_table);
    vector<uc> Cb_compressed = compress(Cb_down, w / k, h / k, C_table, dc_cb, 0);
    vector<uc> Cr_compressed = compress(Cr_down, w / k, h / k, C_table, dc_cr, 0);

    saveDATA(outfile, Y_compressed, Cb_compressed, Cr_compressed, quality, dc_y, dc_cb, dc_cr, k);
}

vector<uc> decompess(const vector<uc>& channel, int dc_len, int ac_len, int& w, int& h, int or_w, int or_h, const int q_table[64], bool is_Y) {
    vector<uc> dc_encoded(dc_len), ac_encoded(ac_len);
    for (int i = 0; i < dc_len;i++)
        dc_encoded[i] = channel[i];

    int ac_start = dc_len;
    for (int i = 0; i < ac_len;i++)
        ac_encoded[i] = channel[ac_start++];

    map<string, int> huf_table = reverse(dc_Huffman);
    vector<DC> dc_vlc = Huf_decodingDC(dc_encoded, huf_table);

    huf_table = (is_Y) ? reverse(AC_Y) : reverse(AC_C);
    vector<AC> ac_rle = Huf_decodingAC(ac_encoded, huf_table);

    vector<int> dc = decodeDC(vlc_decoding(dc_vlc));

    int H = h / 8;
    int W = w / 8;
    int block_i = 0, ac_i = 0, pos = 0;

    vector<vector<vector<double>>> blocks(H * W);

    for (int bi = 0; bi < H; bi++) {
        for (int bj = 0; bj < W; bj++) {
            if (block_i == 4096) {
                cout << "hi";
            }
            vector<int> ac = rle_decoding(ac_rle,pos, 8, 8);

            vector<int> zigzagged(64);
            zigzagged[0] = dc[block_i];
            for (int i = 1; i < 64; i++) {
                zigzagged[i] = ac[i - 1];
            }
            vector<vector<int>> quant = inverseZigzag(zigzagged, 8, 8);
            vector<vector<double>> dct = dequantize(quant, q_table);
            vector<vector<double>> block = DCT_bymatrix(dct, 0);
            blocks[block_i++] = block;
        }
    }
    vector<uc> result = merge_blocks(blocks, w, h, 8, 8);
    w = or_w;
    h = or_h;
    result.resize(or_w * or_h);

    return result;
}

void Image::decompressor(string infile) {

    vector<uc> Y_compressed, Cb_compressed, Cr_compressed; int quality = 0, dc_y, dc_cb, dc_cr, k = 0;
    loadDATA(infile, Y_compressed, Cb_compressed, Cr_compressed, quality, dc_y, dc_cb, dc_cr, k);

    int w = width, h = height;
    vector<uc> Y(w * h);
    vector<uc> Cb(w * h);
    vector<uc> Cr(w * h);

    int Y_table[64], C_table[64];
    new_table(Y_QT, quality, Y_table);
    new_table(CbCr_QT, quality, C_table);

    int cw = w / k, ch = h / k;
    Y = decompess(Y_compressed, dc_y, Y_compressed.size() - dc_y, w, h,orig_w,orig_h, Y_table, 1);
    vector<uc> Cb_down = decompess(Cb_compressed, dc_cb, Cb_compressed.size() - dc_cb, cw, ch, orig_w / k, orig_h / k, C_table, 0);
    vector<uc> Cr_down = decompess(Cr_compressed, dc_cr, Cr_compressed.size() - dc_cr, cw, ch, orig_w / k, orig_h / k, C_table, 0);

    Cb = resize(Cb_down, cw, ch, w, h);
    Cr = resize(Cr_down, cw, ch, w, h);

    for (int i = 0; i < w * h; i++) {
        data[i * 3] = Y[i];
        data[i * 3 + 1] = Cb[i];
        data[i * 3 + 2] = Cr[i];
    }
    to_RGB();
}
