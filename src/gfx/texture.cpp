#include "gfx/texture.hpp"

mg::Texture::Texture() {
    mipmaps = false;
    bpp = 0;
	size = 0;
	data = nullptr;

    minFilter = mg::TEXTURE_FILTER::NEAREST;
    magFilter = mg::TEXTURE_FILTER::NEAREST;
    sWrap = mg::TEXTURE_WRAP::REPEAT;
    tWrap = mg::TEXTURE_WRAP::REPEAT;
}
mg::Texture::~Texture() {
	if(data != nullptr) {
		delete data;
	}
}

bool mg::Texture::setData(unsigned char* d) {
	if(d == nullptr) {
		printf("Texture got nullptr as data!\n");
		return false;
	}

	data = d;

	return true;
}
unsigned char* mg::Texture::getData() {
	return data;
}
unsigned int mg::Texture::getSize() {
	return size;
}
unsigned int mg::Texture::getBPP() {
	return bpp;
}
