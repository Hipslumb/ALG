#include "Image.h"

bool Image::load(string filename) {
	const char* name = filename.c_str();
	data = stbi_load(name, &width, &height, &pixel, 0);
	ifstream file(filename, ios::binary);

	if (data == nullptr) return false;
	data_size = width * height * pixel;

	if (file.is_open()) {
		int w, h;
		uc p, t, cs;
		file.read((char*)&w, 4);
		file.read((char*)&h, 4);
		file.read((char*)&p, 1);
		file.read((char*)&t, 1);
		file.read((char*)&cs, 1);

		if (w == width && h == height && p == pixel) {
			type = t;
			color_space = cs;
			file.close();
			return true;
		}
		file.close();
	}
	color_space = 0;
	if (pixel == 1) {
		type = 0;
		for (int i = 0; i < width * height; i++) {
			if (data[i] != 0 && data[i] != 255) {
				type = 1;
				break;
			}
		}
	}
	else {
		type = 3;
	}

	return true;
}

void Image::save(string filename) {
	const char* name = filename.c_str();

	ofstream file(name, ios::binary);
	file.write((char*)&width, 4);
	file.write((char*)&height, 4);
	file.write((char*)&pixel, 1);
	file.write((char*)&type, 1);
	file.write((char*)&color_space, 1);

	file.write((char*)data, width * height * pixel);
	file.close();
}

void Image::toGrayscale() {
	if (!data || pixel != 3) return;

	data_size = width * height;
	uc* grayData = new uc[data_size];

	for (int i = 0; i < data_size; i++) {
		int r = data[i * 3];
		int g = data[i * 3 + 1];
		int b = data[i * 3 + 2];
		grayData[i] = (uc)(0.299 * r + 0.587 * g + 0.114 * b);
	}

	stbi_image_free(data);
	data = grayData;
	pixel = 1;
	type = 1;
}
void Image::toBW_byrounding() {
	if (!data) return;
	if (pixel == 3) toGrayscale();
	// c' = round(c/255) * 255
	for (int i = 0; i < width * height; i++) {
		data[i] = (data[i] < 128) ? 0 : 255;
	}
	type = 0;
}

void Image::toBW_byDithering() {
	if (!data) return;
	if (pixel == 3) toGrayscale();

	float* buffer = new float[width * height];
	for (int i = 0; i < width * height; i++)
		buffer[i] = data[i];


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			float oldPixel = buffer[i * width + j];
			float newPixel = (oldPixel < 128) ? 0 : 255;
			buffer[i * width + j] = newPixel;

			float error = oldPixel - newPixel;

			if (j + 1 < width)
				buffer[i * width + j + 1] += error * 7 / 16;
			if (i + 1 < height) {
				if (j - 1 >= 0)
					buffer[(i + 1) * width + j - 1] += error * 3 / 16;
				buffer[(i + 1) * width + j] += error * 5 / 16;

				if (j + 1 < width)
					buffer[(i + 1) * width + j + 1] += error * 1 / 16;
			}
		}
	}

	for (int i = 0; i < width* height; i++)
		data[i] = (uc)(buffer[i] > 127 ? 255 : 0);

	delete[] buffer;
	type = 0;
}