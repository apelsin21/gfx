#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <glm/glm.hpp>

namespace gfx {
    class Texture {
        public:
            int bpp;
            glm::vec2 res;
            std::string path;

            virtual bool load(const std::string&) = 0;
    };
}

#endif //TEXTURE_HPP
