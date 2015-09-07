#include "gfx/texture_loader.hpp"

mg::TextureLoader::TextureLoader() {
}
mg::TextureLoader::~TextureLoader() {
}

bool mg::TextureLoader::load(const std::string& p, std::shared_ptr<mg::Texture> out_texture) {
	if(p.empty()) {
		printf("textureloader tried to load texture from empty path.\n");
		return false;
	}

    FIBITMAP* fb = nullptr;
    FREE_IMAGE_FORMAT ff = FreeImage_GetFileType(p.c_str(), 0);

	if(ff == FIF_UNKNOWN) {
		ff = FreeImage_GetFIFFromFilename(p.c_str());
	}

	if(ff != FIF_UNKNOWN && FreeImage_FIFSupportsReading(ff)) {
		fb = FreeImage_Load(ff, p.c_str());
	} else {
		printf("tried to load texture %s, but the format is \
				unsupported by FreeImage.\n", p.c_str());
		return false;
	}

	if(FreeImage_GetBPP(fb) != 32) {
        FIBITMAP* temp = fb;
        fb = FreeImage_ConvertTo32Bits(temp);
        FreeImage_Unload(temp);
	}

	if(FreeImage_GetBits(fb) == nullptr) {
		printf("data loaded by FreeImage is null for unknown reason.\n");
		return false;
	}

    out_texture->setResolution(glm::vec2(FreeImage_GetWidth(fb), FreeImage_GetHeight(fb)));
    out_texture->setBPP(FreeImage_GetBPP(fb));
    out_texture->setPath(p);
	out_texture->setSize((FreeImage_GetWidth(fb) * FreeImage_GetHeight(fb)) * 4);
	out_texture->setData(FreeImage_GetBits(fb));
	FreeImage_Unload(fb);

	return true;
}
