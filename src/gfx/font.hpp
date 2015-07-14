#ifndef FONT_HPP
#define FONT_HPP

#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>

#include <ft2build.h>
#include FT_FREETYPE_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include "gfx/glyph.hpp"

namespace mg {
    class Font {
		protected:
			GLuint id;
        public:
			Font();
			~Font();

            std::map<wchar_t, mg::Glyph> glyphs;

            std::string path;
			std::wstring cacheString;
            glm::vec2 resolution;

			void createID();
			void deleteID();
			void bindID();
			bool hasValidID();
			unsigned int getID();

            bool load(const std::string&, unsigned int);
    };
}

#endif //FONT_HPP
