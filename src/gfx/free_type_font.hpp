#ifndef FREE_TYPE_FONT_HPP
#define FREE_TYPE_FONT_HPP

#include "gfx/font.hpp"

#include <iostream>
#include <algorithm>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>

namespace gfx {
    class FreeTypeFont : public Font {
        protected:
        public:
            FreeTypeFont();
            ~FreeTypeFont();

            bool load(const std::string&, unsigned int);
    };
}

#endif //FREE_TYPE_FONT_HPP
