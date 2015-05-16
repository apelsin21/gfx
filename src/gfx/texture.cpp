#include "gfx/texture.hpp"

mg::Texture::Texture() {
    this->mipmaps = true;
    this->bpp = 0;

    this->minFilter = TEXTURE_FILTER::TEXTURE_FILTER_NEAREST;
    this->magFilter = TEXTURE_FILTER::TEXTURE_FILTER_NEAREST;
    this->sWrap = TEXTURE_WRAP::TEXTURE_WRAP_REPEAT;
    this->tWrap = TEXTURE_WRAP::TEXTURE_WRAP_REPEAT;
}
mg::Texture::~Texture() {
}

FREE_IMAGE_FORMAT mg::Texture::getFreeImageFormatFromPath(const std::string& path) {
   FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str(), 0);
   
   if(format == FIF_UNKNOWN) {
       format = FreeImage_GetFIFFromFilename(path.c_str());
   }
}

bool mg::Texture::loadFromFile(const std::string& path) {
    std::ifstream fileCheck(path);
    if(!fileCheck.good()) {
        std::string errMsg("tried to load texture ");
        errMsg += path;
        errMsg += ", but it doesn't exist.\n";
        throw std::runtime_error(errMsg);
        return false; 
    }

    FREE_IMAGE_FORMAT ff = this->getFreeImageFormatFromPath(path);
    FIBITMAP* fb = nullptr;
    BYTE* pImageData = nullptr;

    if(ff != FIF_UNKNOWN && FreeImage_FIFSupportsReading(ff)) {
        fb = FreeImage_Load(ff, path.c_str());
    } else {
        std::string errMsg("tried to load a texture from ");
        errMsg += path;
        errMsg += ", but FreeImage doesn't support reading that format.\n";
        throw std::runtime_error(errMsg);
        return false;
    }
    
    if(FreeImage_GetBPP(fb) != 32) {
        FIBITMAP* temp = fb;
        fb = FreeImage_ConvertTo32Bits(temp);
        FreeImage_Unload(temp);
    }

    this->resolution = glm::vec2(FreeImage_GetWidth(fb), FreeImage_GetHeight(fb));
    this->bpp = FreeImage_GetBPP(fb);
    this->path = path;
    pImageData = FreeImage_GetBits(fb);
    
    if(pImageData == nullptr) {
        throw std::runtime_error("FreeImage texture is NULL for unknown reason\n");
        return false;
    }

    if(!this->hasValidID()) {
        printf("texture id: %u\n", this->id);
        throw std::runtime_error("FreeImageTexture with invalid id tried to load from file\n");
        return false;
    }

    this->bindID();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->resolution.x, this->resolution.y, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)pImageData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->textureFilterToGLEnum(this->minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->textureFilterToGLEnum(this->magFilter));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->textureWrapToGLEnum(this->sWrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->textureWrapToGLEnum(this->tWrap));

    if(this->mipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    FreeImage_Unload(fb);

    return true;
}

void mg::Texture::createID() {
    if(!this->hasValidID()) {
        glGenTextures(1, &this->id);
        this->bindID(); //Texture name isn't valid until bound
    }
}
void mg::Texture::deleteID() {
    if(this->hasValidID()) {
        glDeleteTextures(1, &this->id);
    }
}
void mg::Texture::bindID() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}
bool mg::Texture::hasValidID() {
    if(glIsTexture(this->id) == GL_TRUE) {
        return true;
    } else {
        return false;
    }
}

GLenum mg::Texture::textureFilterToGLEnum(TEXTURE_FILTER t) {
    switch(t) {
    case TEXTURE_FILTER::TEXTURE_FILTER_NEAREST:
        return GL_NEAREST;
    break;
    case TEXTURE_FILTER::TEXTURE_FILTER_LINEAR:
        return GL_LINEAR;
    break;
    }
}
GLenum mg::Texture::textureWrapToGLEnum(TEXTURE_WRAP t) {
    switch(t) {
    case TEXTURE_WRAP::TEXTURE_WRAP_REPEAT:
        return GL_REPEAT;
    break;
    case TEXTURE_WRAP::TEXTURE_WRAP_MIRRORED_REPEAT:
        return GL_MIRRORED_REPEAT;
    break;
    case TEXTURE_WRAP::TEXTURE_WRAP_CLAMP_TO_EDGE:
        return GL_CLAMP_TO_EDGE;
    break;
    case TEXTURE_WRAP::TEXTURE_WRAP_CLAMP_TO_BORDER:
        return GL_CLAMP_TO_BORDER;
    break;
    }
}
