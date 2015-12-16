#ifndef FONT_HPP
#define FONT_HPP

#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <memory>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <epoxy/gl.h>

#include <glm/glm.hpp>

#include "gfx/glyph.hpp"
#include "gfx/mesh.hpp"

namespace mg {
    class Font {
		protected:
			GLuint m_id;
            std::map<wchar_t, mg::Glyph> m_glyphs;
			std::wstring m_cacheString;
            std::string m_path;
            glm::vec2 m_resolution;
        public:
			Font();
			~Font();

			void createID();
			void deleteID();
			void bindID();
			bool hasValidID();
			unsigned int getID();

            bool load(std::string, unsigned int);

			//std::shared_ptr<mg::Mesh> getMeshFromString(const std::wstring&);

			void render();
    };
}

#endif //FONT_HPP
