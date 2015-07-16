#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <stdio.h>
#include <fstream>

#include <glm/glm.hpp>

#include <FreeImage.h>

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
			unsigned int size, bpp;
            bool mipmaps;

            Texture();
			~Texture();

			bool setData(unsigned char*);
			unsigned char* getData();

			unsigned int getSize();
			unsigned int getBPP();
    };
}

#endif //TEXTURE_HPP
