#include "gfx/gl_texture.hpp"

mg::GLTexture::GLTexture() : Texture() {
	this->fb = nullptr;
    createID();
}
mg::GLTexture::~GLTexture() {
    deleteID();
	FreeImage_Unload(this->fb);
}

void mg::GLTexture::createID() {
    if(!hasValidID()) {
        glGenTextures(1, &this->id);
        bindID();
    }
}
void mg::GLTexture::deleteID() {
    if(hasValidID()) {
        glDeleteTextures(1, &this->id);
    }
}
void mg::GLTexture::bindID() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}
bool mg::GLTexture::hasValidID() {
    if(glIsTexture(this->id) == GL_TRUE) {
        return true;
    } else {
        return false;
    }
}
unsigned int mg::GLTexture::getID() {
	return this->id;
}
bool mg::GLTexture::load(const std::string& p) {
    std::ifstream fileCheck(p);
    if(!fileCheck.good()) {
        printf("Tried to load texture %s, but it doesn't exist.\n", p.c_str());
		return false;
    }

	this->ff = FreeImage_GetFileType(p.c_str(), 0);

   	if(this->ff == FIF_UNKNOWN) {
       this->ff = FreeImage_GetFIFFromFilename(p.c_str());
   	}

    if(this->ff != FIF_UNKNOWN && FreeImage_FIFSupportsReading(this->ff)) {
        this->fb = FreeImage_Load(this->ff, p.c_str());
    } else {
        printf("Tried to load texture %s, but the format is unsupported by FreeImage.\n", p.c_str());
		return false;
    }

	//Textures are always 32 bit colour
    if(FreeImage_GetBPP(this->fb) != 32) {
        FIBITMAP* temp = this->fb;
        this->fb = FreeImage_ConvertTo32Bits(temp);
        FreeImage_Unload(temp);
    }

    if(FreeImage_GetBits(this->fb) == nullptr) {
        printf("Texture %s data is NULL for unknown reason\n", p.c_str());
		return false;
    }

    this->resolution 	= 	glm::vec2(FreeImage_GetWidth(this->fb), FreeImage_GetHeight(this->fb));
    this->bpp 			= 	FreeImage_GetBPP(this->fb);
    this->path 			= 	p;
	this->size 			= 	(resolution.x * resolution.y) * 4;
	this->data 			= 	FreeImage_GetBits(this->fb);

    if(!hasValidID()) {
        printf("GLTexture %s has invalid GL handle.\n", p.c_str());
        return false;
    }

    bindID();

    glTexImage2D(
		GL_TEXTURE_2D,
    	0,
    	textureFormatToInt(mg::TEXTURE_FORMAT::RGBA8),
    	this->resolution.x, this->resolution.y,
    	0,
    	textureFormatToInt(mg::TEXTURE_FORMAT::BGRA),
    	GL_UNSIGNED_BYTE,
    	(GLvoid*)this->data
	);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilterToInt(this->minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilterToInt(this->magFilter));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapToInt(this->sWrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapToInt(this->tWrap));

    if(this->mipmaps) {
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
