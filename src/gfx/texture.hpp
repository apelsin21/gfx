#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <stdio.h>

#include <glm/glm.hpp>

namespace mg {
    enum class TEXTURE_FILTER {
        NEAREST,
        LINEAR,
    };
    enum class TEXTURE_WRAP {
        REPEAT,
        MIRRORED_REPEAT,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER,
    };
    enum class TEXTURE_FORMAT {
        RGBA8,
        BGRA,
    };

    class Texture {
		protected:
        public:
			unsigned char* data;
            TEXTURE_FILTER minFilter, magFilter;
            TEXTURE_WRAP sWrap, tWrap;
            TEXTURE_FORMAT internalFormat, format;
            glm::vec2 resolution;
            std::string path;
            int bpp;
            bool mipmaps;

            Texture();

			virtual bool setData(unsigned char*) = 0;
    };
}

#endif //TEXTURE_HPP
