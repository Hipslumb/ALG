#include "fun.h"

//Y = 0.299 * R + 0.587 * G + 0.114 * B
//Cb = -0.1687 * R - 0.3313 * G + 0.5 * B + 128
//Cr = 0.5 * R - 0.4187 * G - 0.0813 * B + 128

void Image::to_YCbCr() {
    if (!data || pixel != 3) return;

    int size = width * height;
    uc* ycbcr = new uc[size * 3];

    for (int i = 0; i < size; i++) {
        float r = data[i * 3];
        float g = data[i * 3 + 1];
        float b = data[i * 3 + 2];

        float Y = 0.299 * r + 0.587 * g + 0.114 * b;
        float Cb = - 0.1687 * r - 0.3313 * g + 0.5 * b + 128;
        float Cr = 0.5 * r - 0.4187 * g - 0.0813 * b + 128;

        ycbcr[i * 3] = (uc)min(255.0f, max(0.0f, Y));
        ycbcr[i * 3 + 1] = (uc)min(255.0f, max(0.0f, Cb));
        ycbcr[i * 3 + 2] = (uc)min(255.0f, max(0.0f, Cr));
    }

    stbi_image_free(data);
    data = ycbcr;
    color_space = 1;
}

//R = Y + 1.402 * (Cr - 128)
//G = Y - 0.34414 * (Cb - 128) - 0.71414 * (Cr - 128)
//B = Y + 1.772 * (Cb - 128)

void Image::to_RGB() {
    if (!data || pixel != 3) return;

    int size = width * height;
    uc* rgbData = new uc[size * 3];

    for (int i = 0; i < size; i++) {
        float Y = data[i * 3];
        float Cb = data[i * 3 + 1];
        float Cr = data[i * 3 + 2];

        float R = Y + 1.402 * (Cr - 128);
        float G = Y - 0.34414 * (Cb - 128) - 0.71414 * (Cr - 128);
        float B = Y + 1.772f * (Cb - 128);

        rgbData[i * 3] = (uc)min(255.0f, max(0.0f, R));
        rgbData[i * 3 + 1] = (uc)min(255.0f, max(0.0f, G));
        rgbData[i * 3 + 2] = (uc)min(255.0f, max(0.0f, B));
    }

    stbi_image_free(data);
    data = rgbData;
    type = 2;
}

void Image::saveComponents(string prefix) {
    if (!data || pixel != 3) return;

    int size = width * height;

    uc* Y = new uc[size];
    for (int i = 0; i < size; i++) {
        Y[i] = data[i * 3];
    }
    stbi_write_png((prefix + "_Y.png").c_str(), width, height, 1, Y, 0);
    delete[] Y;

    uc* Cb = new uc[size];
    for (int i = 0; i < size; i++) {
        Cb[i] = data[i * 3 + 1];
    }
    stbi_write_png((prefix + "_Cb.png").c_str(), width, height, 1, Cb, 0);
    delete[] Cb;

    uc* Cr = new uc[size];
    for (int i = 0; i < size; i++) {
        Cr[i] = data[i * 3 + 2];
    }
    stbi_write_png((prefix + "_Cr.png").c_str(), width, height, 1, Cr, 0);
    delete[] Cr;
}