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
        return false;
    }
    
    if(!fb) {
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

    FreeImage_Unload(fb);

    return true;
}
