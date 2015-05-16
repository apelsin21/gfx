#ifndef FONT_HPP
#define FONT_HPP

#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtx/type_aligned.hpp>

#include "gfx/gl_object.hpp"
#include "gfx/glyph.hpp"

namespace mg {
    class Font : public GLObject {
        public:
			Font();
			~Font();

            std::map<wchar_t, mg::Glyph> glyphs;

            std::string path;
			std::wstring cacheString;
            glm::i32vec2 resolution;

			void createID();
			void deleteID();
			void bindID();
			bool hasValidID();

            bool loadFromFile(const std::string&, unsigned int);
    };
}

#endif //FONT_HPP
