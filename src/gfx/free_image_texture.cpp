#include "gfx/free_image_texture.hpp"

gfx::FreeImageTexture::FreeImageTexture() {
    this->bpp = 0;
}
gfx::FreeImageTexture::~FreeImageTexture() {
}

FREE_IMAGE_FORMAT gfx::FreeImageTexture::getFreeImageFormatFromPath(const std::string& path) {
   FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str(), 0);
   
   if(format == FIF_UNKNOWN) {
       format = FreeImage_GetFIFFromFilename(path.c_str());
   }
}

bool gfx::FreeImageTexture::loadFromFile(const std::string& path) {
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
