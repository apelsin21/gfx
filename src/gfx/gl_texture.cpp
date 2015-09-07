#include "gfx/texture.hpp"

mg::Texture::Texture() {
    createID();
}
mg::Texture::~Texture() {
    deleteID();
}

void mg::Texture::createID() {
    if(!hasValidID()) {
        glGenTextures(1, &_id);
        bindID();
    }
}
void mg::Texture::deleteID() {
    if(hasValidID()) {
        glDeleteTextures(1, &_id);
    }
}
void mg::Texture::bindID() {
    glBindTexture(GL_TEXTURE_2D, _id);
}
bool mg::Texture::hasValidID() {
    if(glIsTexture(_id) == GL_TRUE) {
        return true;
    } else {
        return false;
    }
}
unsigned int mg::Texture::getID() {
	return _id;
}
void mg::Texture::setData(unsigned char* data) {
	_data = data;
}
bool mg::Texture::load() {
    bindID();


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilterToInt(filter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilterToInt(filter));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapToInt(wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapToInt(wrap));

	this->minFilter = filter;
	this->magFilter = filter;

	this->sWrap = wrap;
	this->tWrap = wrap;


	return true;
}

int mg::Texture::textureFilterToInt(TEXTURE_FILTER t) {
    switch(t) {
    case TEXTURE_FILTER::NEAREST:
        return GL_NEAREST;
    case TEXTURE_FILTER::LINEAR:
        return GL_LINEAR;
    }
}
int mg::Texture::textureWrapToInt(TEXTURE_WRAP t) {
    switch(t) {
    case TEXTURE_WRAP::REPEAT:
        return GL_REPEAT;
    case TEXTURE_WRAP::MIRRORED_REPEAT:
        return GL_MIRRORED_REPEAT;
    case TEXTURE_WRAP::CLAMP_TO_EDGE:
        return GL_CLAMP_TO_EDGE;
    case TEXTURE_WRAP::CLAMP_TO_BORDER:
        return GL_CLAMP_TO_BORDER;
    }
}
int mg::Texture::textureFormatToInt(TEXTURE_FORMAT format) {
    switch(format) {
	case TEXTURE_FORMAT::RGBA8:
        return GL_RGBA8;
    case TEXTURE_FORMAT::BGRA:
        return GL_BGRA;
    }
}
