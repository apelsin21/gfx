#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include <string>
#include <memory>

#include <FreeImage.h>

#include "gfx/texture.hpp"

namespace mg {
	class TextureLoader {
		protected:
		public:
			TextureLoader();
			~TextureLoader();

			bool load(const std::string&, std::shared_ptr<mg::Texture> out_texture);
	};
}

#endif //TEXTURE_LOADER_HPP
