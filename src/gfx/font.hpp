#ifndef FONT_HPP
#define FONT_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>

#include "gfx/gl_object.hpp"
#include "gfx/glyph.hpp"
#include "gfx/sprite_batch.hpp"

namespace gfx {
    class Font : public GLObject {
        public:
			Font();
			~Font();

            std::vector<Glyph> glyphs;

            std::string path;
            glm::vec2 res;

			void createID();
			void deleteID();
			void bindID();
			bool hasValidID();

            bool loadFromFile(const std::string&, unsigned int);
    };
}

#endif //FONT_HPP
