#include "gfx/free_image_texture_loader.hpp"

mg::FreeImageTextureLoader::FreeImageTextureLoader() {
}
mg::FreeImageTextureLoader::~FreeImageTextureLoader() {
}

bool mg::FreeImageTextureLoader::load(const std::string& path, mg::Texture& texture) {
    std::ifstream fileCheck(path);
    if(!fileCheck.good()) {
        printf("Tried to load texture %s, but it doesn't exist.\n", path);
		return false;
    }

    FREE_IMAGE_FORMAT ff = getFreeImageFormatFromPath(path);
    FIBITMAP* fb = nullptr;

    if(ff != FIF_UNKNOWN && FreeImage_FIFSupportsReading(ff)) {
        fb = FreeImage_Load(ff, path.c_str());
    } else {
        printf("Tried to load texture %s, but the format is unsupported by FreeImage.\n", path.c_str());
		return false;
    }

    if(FreeImage_GetBPP(fb) != 32) {
        FIBITMAP* temp = fb;
        fb = FreeImage_ConvertTo32Bits(temp);
        FreeImage_Unload(temp);
    }

	unsigned char* data = FreeImage_GetBits(fb);

    if(data == nullptr) {
        printf("Texture %s data is NULL for unknown reason\n", path.c_str());
		return false;
    }

    texture.resolution = glm::vec2(FreeImage_GetWidth(fb), FreeImage_GetHeight(fb));
    texture.bpp = FreeImage_GetBPP(fb);
    texture.path = path;

	if(!texture.setData(data)) {
		return false;
	}

    FreeImage_Unload(fb);

    return true;
}

FREE_IMAGE_FORMAT mg::FreeImageTextureLoader::getFreeImageFormatFromPath(const std::string& path) {
   FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str(), 0);

   if(format == FIF_UNKNOWN) {
       format = FreeImage_GetFIFFromFilename(path.c_str());
   }
}
