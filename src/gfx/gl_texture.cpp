#include "gfx/gl_texture.hpp"

mg::GLTexture::GLTexture() : Texture() {
    createID();
}
mg::GLTexture::~GLTexture() {
    deleteID();
}

void mg::GLTexture::createID() {
    if(!hasValidID()) {
        glGenTextures(1, &id);
        bindID();
    }
}
void mg::GLTexture::deleteID() {
    if(hasValidID()) {
        glDeleteTextures(1, &id);
    }
}
void mg::GLTexture::bindID() {
    glBindTexture(GL_TEXTURE_2D, id);
}
bool mg::GLTexture::hasValidID() {
    if(glIsTexture(id) == GL_TRUE) {
        return true;
    } else {
        return false;
    }
}
unsigned int mg::GLTexture::getID() {
	return this->id;
}
bool mg::GLTexture::setData(unsigned char* data) {
	if(data == nullptr) {
		printf("GLTexture got nullptr as data\n");
		return false;
	}

    if(!hasValidID()) {
        printf("GLTexture %s has invalid GL handle.\n", path.c_str());
        return false;
    }

    bindID();

    glTexImage2D(
		GL_TEXTURE_2D,
    	0,
    	textureFormatToInt(mg::TEXTURE_FORMAT::RGBA8),
    	resolution.x, resolution.y,
    	0,
    	textureFormatToInt(mg::TEXTURE_FORMAT::BGRA),
    	GL_UNSIGNED_BYTE,
    	(GLvoid*)data
	);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilterToInt(minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilterToInt(magFilter));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapToInt(sWrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapToInt(tWrap));

    if(mipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

	return true;
}

int mg::GLTexture::textureFilterToInt(TEXTURE_FILTER t) {
    switch(t) {
    case TEXTURE_FILTER::NEAREST:
        return GL_NEAREST;
    case TEXTURE_FILTER::LINEAR:
        return GL_LINEAR;
    }
}
int mg::GLTexture::textureWrapToInt(TEXTURE_WRAP t) {
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
int mg::GLTexture::textureFormatToInt(TEXTURE_FORMAT format) {
    switch(format) {
	case TEXTURE_FORMAT::RGBA8:
        return GL_RGBA8;
    case TEXTURE_FORMAT::BGRA:
        return GL_BGRA;
    }
}
