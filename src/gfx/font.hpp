#ifndef FONT_HPP
#define FONT_HPP

#include "gfx/glyph.hpp"

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace gfx {
    class Font {
        public:
            std::vector<Glyph> glyphs;

            std::string path;
            glm::vec2 res;

            virtual bool load(const std::string&, unsigned int) = 0;
    };
}

#endif //FONT_HPP
