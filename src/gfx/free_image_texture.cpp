#include "gfx/free_image_texture.hpp"

gfx::FreeImageTexture::FreeImageTexture() {
    this->width = 0;
    this->height = 0;
    this->bpp = 0;
}
gfx::FreeImageTexture::~FreeImageTexture() {
}

int gfx::FreeImageTexture::getWidth() {
    return this->width;
}
int gfx::FreeImageTexture::getHeight() {
    return this->height;
}
int gfx::FreeImageTexture::getBPP() {
    return this->bpp;
}
std::string gfx::FreeImageTexture::getPath() {
    return this->path;
}

FREE_IMAGE_FORMAT gfx::FreeImageTexture::getFreeImageFormatFromPath(const std::string& path) {
   FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str(), 0);
   
   if(format == FIF_UNKNOWN) {
       format = FreeImage_GetFIFFromFilename(path.c_str());
   }
}

bool gfx::FreeImageTexture::load(const std::string& path) {
    if(path.empty()) {
        return false;
    }
    
    FREE_IMAGE_FORMAT format = this->getFreeImageFormatFromPath(path);
    FIBITMAP* bitmap = nullptr;
    
    if(FreeImage_FIFSupportsReading(format)) {
        bitmap = FreeImage_Load(format, path.c_str());
    } else {
        return false;
    }
    
    if(!bitmap) {
        return false;
    }
   
    if(FreeImage_GetBPP(bitmap) != 32) {
        FIBITMAP* temp = FreeImage_ConvertTo32Bits(bitmap);
        
        FreeImage_Unload(bitmap);
        bitmap = temp;
    }

    this->width = FreeImage_GetWidth(bitmap);
    this->height = FreeImage_GetHeight(bitmap);
    this->bpp = FreeImage_GetBPP(bitmap);
    this->path = path;

    FreeImage_Unload(bitmap);

    return true;
}
