#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include "gfx/gl_object.hpp"

namespace gfx {
    class Texture : public GLObject {
        public:
            int bpp;
            glm::vec2 res;
            std::string path;

            virtual bool loadFromFile(const std::string&) = 0;

			virtual void createID();
			virtual void deleteID();
			virtual void bindID();
			virtual bool hasValidID();
    };
}

#endif //TEXTURE_HPP
