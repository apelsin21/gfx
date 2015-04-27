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
    if(path.empty()) {
        throw std::runtime_error("tried to load texture from empty path");
        return false;
    }
    
    FREE_IMAGE_FORMAT ff = this->getFreeImageFormatFromPath(path);
    FIBITMAP* fb = nullptr;
    
    if(FreeImage_FIFSupportsReading(ff)) {
        fb = FreeImage_Load(ff, path.c_str());
    } else {
        std::string errMsg("tried to load a texture from ");
        errMsg += path;
        errMsg += ", but FreeImage doesn't support reading that format!\n";
        throw std::runtime_error(errMsg);
        return false;
    }
    
    if(FreeImage_GetBPP(fb) != 32) {
        FIBITMAP* temp = FreeImage_ConvertTo32Bits(fb);
        
        FreeImage_Unload(fb);
        fb = temp;
    }

    this->res = glm::vec2(FreeImage_GetWidth(fb), FreeImage_GetHeight(fb));
    this->bpp = FreeImage_GetBPP(fb);
    this->path = path;

    if(!this->hasValidID()) {
        printf("texture id: %u\n", this->id);
        throw std::runtime_error("FreeImageTexture with invalid id tried to load from file\n");
        return false;
    }

    this->bindID();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->textureFilterToGLEnum(this->minFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->textureFilterToGLEnum(this->magFilter));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->textureWrapToGLEnum(this->sWrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->textureWrapToGLEnum(this->tWrap));

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->res.x, this->res.y, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(fb));

    if(this->mipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    FreeImage_Unload(fb);

    return true;
}
