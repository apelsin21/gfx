#include "gfx/texture.hpp"

gfx::Texture::Texture() {
    this->width = 0;
    this->height = 0;
    this->bpp = 0;
}
gfx::Texture::~Texture() {
}

FREE_IMAGE_FORMAT gfx::Texture::getFreeImageFormatFromPath(const std::string& path) {
   FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str(), 0);
   
   if(format == FIF_UNKNOWN) {
       format = FreeImage_GetFIFFromFilename(path.c_str());
   }
}

bool gfx::Texture::load(const std::string& path) {
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
