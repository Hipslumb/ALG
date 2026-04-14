#include "fun.h"

vector<int> zigzag(const vector<vector<int>>& matrix) {
    int N = matrix.size();
    int M = matrix[0].size();
    vector<int> result(N * M);

    int row = 0, col = 0;
    bool goingUp = true;

    for (int i = 0; i < N * M; i++) {
        result[i] = matrix[row][col];
        if (goingUp) {
            if (col == M - 1) {
                row++;
                goingUp = false;
            }
            else if (row == 0) {
                col++;
                goingUp = false;
            }
            else {
                row--;
                col++;
            }
        }
        else {
            if (row == N - 1) {
                col++;
                goingUp = true;
            }
            else if (col == 0) {
                row++;
                goingUp = true;
            }
            else {
                row++;
                col--;
            }
        }
    }

    return result;
}
//////////////diff/////////////////////////////
vector<int> encodeDC(const vector<int>& dc) {
    if (dc.empty()) return {};

    vector<int> diff(dc.size());

    diff[0] = dc[0];

    for (int i = 1; i < (int)dc.size(); i++) {
        diff[i] = dc[i] - dc[i - 1];
    }

    return diff;
}

vector<int> decodeDC(const vector<int>& diff) {
    if (diff.empty()) return {};

    vector<int> dc(diff.size());

    dc[0] = diff[0];

    for (int i = 1; i < (int)diff.size(); i++) {
        dc[i] = dc[i - 1] + diff[i];
    }

    return dc;
}

///////help////////////////////////////
int getSize(int code) {
    if (code == 0) return 0;

    int absVal = abs(code);
    int size = 0;
    while (absVal > 0) {
        size++;
        absVal >>= 1;
    }
    return size;
}

int encoded_code(int code, int size) {
    if (code >= 0)
        return code;
    return (1 << size) - 1 - abs(code);
}

int decoded_code(int encoded, int size) {
    if (encoded < (1 << (size - 1)))
        return encoded - (1 << size) + 1;
    return encoded;
}

////////RLE////////////////////////////////////////////////////////////////
vector<AC> rle_encoding(const vector<int>& ac, int N, int M) {
    vector<AC> result;

    int run = 0;
    int acCount = N * M - 1;

    for (int i = 0; i < acCount; i++) {
        if (ac[i] == 0) {
            run++;
            if (run == 16) {
                result.push_back({ 15, 0, 0 });
                run = 0;
            }
        }
        else {
            int size = getSize(ac[i]);
            int code = encoded_code(ac[i], size);

            result.push_back({ run, size, code });
            run = 0;
        }
    }

    result.push_back({ 0, 0, 0 });

    return result;
}

vector<int> rle_decoding(const vector<AC>& rleCodes) {
    vector<int> result;
    int acCount = N * M - 1;

    for (const auto& code : rleCodes) {
        if (code.run == 0 && code.size == 0 && code.code == 0) {
            while ((int)result.size() < acCount)
                result.push_back(0);
            
            break;
        }

        if (code.run == 15 && code.size == 0 && code.code == 0) {
            for (int i = 0; i < 16; i++) 
                result.push_back(0);
            continue;
        }

        for (int i = 0; i < code.run; i++)
            result.push_back(0);

        int val = decoded_code(code.code, code.size);
        result.push_back(val);
    }

    while ((int)result.size() > acCount)
        result.pop_back();
    
    return result;
}


//////////VLC/////////////////////////////////////////////////////////////
vector<DC> vlc_encoding(const vector<int>& diffs) {
    vector<DC> result;

    for (int diff : diffs) {
        int size = getSize(diff);
        int code = encoded_code(diff, size);
        result.push_back({ size, code });
    }

    return result;
}

vector<int> vlc_decoding(const vector<DC>& vlcData) {
    vector<int> result;

    for (const auto& vlc : vlcData) {
        int value = decoded_code(vlc.code, vlc.size);
        result.push_back(value);
    }

    return result;
}

/////////HUFFMAN///////////////////////////////////////////
vector<uc> Huf_encoding(const vector<int>& keys, map<int, string>& huf_table) {
    vector<uc> encoded;
    string bits;

    for (int key : keys) {
        bits += huf_table[key];
    }

    encoded = packBits(bits);
    return encoded;
}

vector<int> Huf_decoding(const vector<uc>& encoded, map<string, int>& huf_table) {
    vector<int> decoded;

    if (encoded.empty()) return decoded;

    int last_size = encoded[0];

    string bits;
    for (int i = 1; i < (int)encoded.size(); i++) {
        uc b = encoded[i];
        for (int j = 7; j >= 0; j--) {
            bits += ((b >> j) & 1) ? '1' : '0';
        }
    }

    if (last_size < 8) {
        bits = bits.substr(0, bits.size() - (8 - last_size));
    }

    string cur;
    for (char bit : bits) {
        cur += bit;
        auto it = huf_table.find(cur);
        if (it != huf_table.end()) {
            decoded.push_back(it->second);
            cur = "";
        }
    }

    return decoded;
}
//////////////for huffman//////////////////////

vector<uc> packBits(const string& bits) {
    vector<uc> encoded;

    if (bits.empty()) {
        encoded.push_back(0);
        return encoded;
    }

    int last_size = bits.size() % 8;
    if (last_size == 0) last_size = 8;
    encoded.push_back((uc)last_size);

    for (int i = 0; i < (int)bits.size(); i += 8) {
        uc byte = 0;
        for (int j = 0; j < 8 && i + j < (int)bits.size(); j++) {
            if (bits[i + j] == '1') {
                byte |= (1 << (7 - j));
            }
        }
        encoded.push_back(byte);
    }

    return encoded;
}

vector<uc> encodeDC_full(const vector<DC>& dcVLC, map<int, string>& hufTable) {
    string bits;

    for (const auto& vlc : dcVLC) {
        int size = vlc.size;
        int code = vlc.code;

        bits += hufTable[size];

        for (int i = size - 1; i >= 0; i--) {
            bits += ((code >> i) & 1) ? '1' : '0';
        }
    }
    return packBits(bits);
}

vector<uc> encodeAC_full(const vector<AC>& acVLC, map<int, string>& hufTable) {
    string bits;

    for (const auto& vlc : acVLC) {
        //(0,0,0)
        if (vlc.run == 0 && vlc.size == 0 && vlc.code == 0) {
            bits += hufTable[0x00];
            continue;
        }
        //(15,0,0)
        if (vlc.run == 15 && vlc.size == 0 && vlc.code == 0) {
            bits += hufTable[0xF0];
            continue;
        }
        int key = (vlc.run << 4) | vlc.size;
        bits += hufTable[key];

        for (int i = vlc.size - 1; i >= 0; i--) {
            bits += ((vlc.code >> i) & 1) ? '1' : '0';
        }
    }

    return packBits(bits);
}