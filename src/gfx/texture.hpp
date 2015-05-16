#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <stdio.h>
#include <stdexcept>
#include <fstream>

#include <FreeImage.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include "gfx/gl_object.hpp"

namespace mg {
    enum TEXTURE_FILTER {
        TEXTURE_FILTER_NEAREST,
        TEXTURE_FILTER_LINEAR,
    };
    enum TEXTURE_WRAP {
        TEXTURE_WRAP_REPEAT,
        TEXTURE_WRAP_MIRRORED_REPEAT,
        TEXTURE_WRAP_CLAMP_TO_EDGE,
        TEXTURE_WRAP_CLAMP_TO_BORDER 
    };

    class Texture : public GLObject {
		protected:
            FREE_IMAGE_FORMAT getFreeImageFormatFromPath(const std::string&);
        public:
            TEXTURE_FILTER minFilter, magFilter;
            TEXTURE_WRAP sWrap, tWrap;
            int bpp;
            bool mipmaps;
            glm::vec2 resolution;
            std::string path;

            Texture();
			~Texture();

            bool loadFromFile(const std::string&);

			void createID();
			void deleteID();
			void bindID();
			bool hasValidID();

            GLenum textureFilterToGLEnum(TEXTURE_FILTER);
            GLenum textureWrapToGLEnum(TEXTURE_WRAP);
    };
}

#endif //TEXTURE_HPP
