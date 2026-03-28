#include "Header.h"
class Image
{
public:
	int width;
	int height;
	int pixel; //1 - rw or grey, 3 - RGB
	int type; //0 - rw, 1 - grey, 2 - RGB
	uc* data;
	int data_size;

	Image() {
		data = nullptr;
	}
	~Image() {
		if (data) stbi_image_free(data);
	};
	bool load(const char* name);
	void save(const char* name);
	void compare(const char* name, const char* rawname);

};

inline bool Image::load(const char* name) {
	data = stbi_load(name, &width, &height, &pixel, 0);
	if (data == nullptr) return false;
	if (pixel == 1) {
		type = 0;
		for (int i = 0;i < width * height;i++)
			if (data[i] != 0 && data[i] != 255) {
				type = 1;
				break;
			}
	}
	else type = 3;

	return true;
}

inline void Image::save(const char* name) {
	ofstream file(name, ios::binary);
	file.write((char*)&width, 4);
	file.write((char*)&height, 4);
	file.write((char*)&pixel, 1);
	file.write((char*)&type, 1);
	file.write((char*)data, width * height * pixel);
	file.close();
}
void create_raw();