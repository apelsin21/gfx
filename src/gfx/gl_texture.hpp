#ifndef GL_TEXTURE_HPP
#define GL_TEXTURE_HPP

#include <string>
#include <stdio.h>

#include <epoxy/gl.h>

#include "gfx/texture.hpp"

namespace mg {
    class GLTexture : public Texture {
		protected:
			GLuint id;
			unsigned char* data;
            int textureFilterToInt(TEXTURE_FILTER);
            int textureWrapToInt(TEXTURE_WRAP);
            int textureFormatToInt(TEXTURE_FORMAT);

    		FIBITMAP* fb = nullptr;
    		FREE_IMAGE_FORMAT ff;
        public:
            GLTexture();
			~GLTexture();

			void createID();
			void deleteID();
			void bindID();
			bool hasValidID();
			unsigned int getID();

			bool load(const std::string&, mg::TEXTURE_FILTER, mg::TEXTURE_WRAP);
    };
}

#endif //GL_TEXTURE_HPP
