#pragma once
#include "fun.h"
class Bits {
private:
    vector<unsigned char> bytes;
    unsigned char buff = 0;
    int bits_inbuff = 0;

public:
    void write_bits(int code, int size) {
        for (int i = size - 1; i >= 0; i--) {
            buff = (buff << 1) | ((code >> i) & 1);
            bits_inbuff++;

            if (bits_inbuff == 8) {
                bytes.push_back(buff);
                buff = 0;
                bits_inbuff = 0;
            }
        }
    }

    vector<unsigned char> get_bytes() {
        if (bits_inbuff > 0) {
            buff <<= (8 - bits_inbuff);
            bytes.push_back(buff);
        }
        return bytes;
    }
};