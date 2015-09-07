#ifndef GL_TEXTURE_HPP
#define GL_TEXTURE_HPP

#include <string>
#include <stdio.h>

#include <epoxy/gl.h>

#include "gfx/texture.hpp"

namespace mg {
    class GLTexture : public Texture {
		protected:
        public:
            GLTexture();
			~GLTexture();

    };
}

#endif //GL_TEXTURE_HPP
