#include "gfx/texture.hpp"

mg::Texture::Texture() {
    _mipmaps = false;
    _bpp = 0;
	_size = 0;
	_id = 0;

	_format = mg::TextureFormat::RGBA8;
	_internalFormat = mg::TextureFormat::BGRA;
    _filter = mg::TextureFilter::Nearest;
    _wrap = mg::TextureWrap::Repeat;

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
}
mg::Texture::~Texture() {
	if(glIsTexture(_id) == GL_TRUE) {
		glDeleteTextures(1, &_id);
	}
}

bool mg::Texture::upload(unsigned char* data) {
	glBindTexture(GL_TEXTURE_2D, _id);

    glTexImage2D(
		GL_TEXTURE_2D,
    	0,
    	_textureFormatToInt(_format),
    	_resolution.x, _resolution.y,
    	0,
    	_textureFormatToInt(_internalFormat),
    	GL_UNSIGNED_BYTE,
    	(GLvoid*)data
	);

	setFilter(_filter);
	setWrap(_wrap);

    if(_mipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

	return true;
}

void mg::Texture::setSize(unsigned int size) {
	_size = size;
}
unsigned int mg::Texture::getSize() const {
	return _size;
}

void mg::Texture::setBPP(unsigned int bpp) {
	_bpp = bpp;
}
unsigned int mg::Texture::getBPP() const {
	return _bpp;
}

void mg::Texture::setPath(const std::string& path) {
	_path = path;
}
std::string mg::Texture::getPath() const {
	return _path;
}

void mg::Texture::setResolution(const glm::vec2& resolution) {
	_resolution = resolution;
}
glm::vec2 mg::Texture::getResolution() const {
	return _resolution;
}

void mg::Texture::setFilter(mg::TextureFilter filter) {
	_filter = filter;

	glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _textureFilterToInt(_filter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _textureFilterToInt(_filter));

}
mg::TextureFilter mg::Texture::getFilter() const {
	return _filter;
}

void mg::Texture::setWrap(mg::TextureWrap wrap) {
	_wrap = wrap;

	glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _textureWrapToInt(_wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _textureWrapToInt(_wrap));
}
mg::TextureWrap mg::Texture::getWrap() const {
	return _wrap;
}

void mg::Texture::setFormat(mg::TextureFormat format) {
	_format = format;
}
mg::TextureFormat mg::Texture::getFormat() const {
	return _format;
}
void mg::Texture::setInternalFormat(mg::TextureFormat internalFormat) {
	_internalFormat = internalFormat;
}
mg::TextureFormat mg::Texture::getInternalFormat() const {
	return _internalFormat;
}

void mg::Texture::setIsMipMapped(bool mipmaps) {
	_mipmaps = mipmaps;
}
bool mg::Texture::isMipMapped() const {
	return _mipmaps;
}

int mg::Texture::_textureFilterToInt(mg::TextureFilter f) {
    switch(f) {
	case mg::TextureFilter::Nearest:
        return GL_NEAREST;
	case mg::TextureFilter::Linear:
        return GL_LINEAR;
	default:
		printf("got unhandled texture filter %i, returning GL_NEAREST.\n", (int)f);
        return GL_NEAREST;
    }
}
int mg::Texture::_textureWrapToInt(mg::TextureWrap t) {
    switch(t) {
	case mg::TextureWrap::Repeat:
        return GL_REPEAT;
	case mg::TextureWrap::Mirrored_Repeat:
        return GL_MIRRORED_REPEAT;
	case mg::TextureWrap::Clamp_To_Edge:
        return GL_CLAMP_TO_EDGE;
	case mg::TextureWrap::Clamp_To_Border:
        return GL_CLAMP_TO_BORDER;
	default:
		printf("got unhandled texture wrap %i, returning GL_REPEAT.\n", (int)t);
        return GL_REPEAT;
    }
}
int mg::Texture::_textureFormatToInt(mg::TextureFormat format) {
    switch(format) {
	case mg::TextureFormat::RGBA8:
        return GL_RGBA8;
	case mg::TextureFormat::BGRA:
        return GL_BGRA;
	case mg::TextureFormat::RGB:
        return GL_RGB;
	case mg::TextureFormat::RGBA:
        return GL_RGBA;
	default:
		printf("got unhandled texture format %i, returning GL_RGBA8.\n", (int)format);
		return GL_RGBA8;
    }
}

void mg::Texture::setGLHandle(unsigned int i) {
	if(glIsTexture(_id) == GL_TRUE) {
		glDeleteTextures(1, &_id);
	}

	_id = i;
}
unsigned int mg::Texture::getGLHandle() const {
	return _id;
}
