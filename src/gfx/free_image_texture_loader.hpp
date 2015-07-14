#ifndef FREE_IMAGE_TEXTURE_LOADER_HPP
#define FREE_IMAGE_TEXTURE_LOADER_HPP

#include <cstdio>
#include <string>
#include <fstream>

#include <FreeImage.h>

#include <glm/glm.hpp>

#include "gfx/texture.hpp"

namespace mg {
	class FreeImageTextureLoader {
		protected:
            FREE_IMAGE_FORMAT getFreeImageFormatFromPath(const std::string&);
		public:
			FreeImageTextureLoader();
			~FreeImageTextureLoader();

			bool load(const std::string&, mg::Texture&);
	};
}

#endif //FREE_IMAGE_TEXTURE_LOADER_HPP
