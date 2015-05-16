#ifndef GLYPH_HPP
#define GLYPH_HPP

#include <glm/glm.hpp>

namespace mg {
    class Glyph {
        public:
            glm::vec2 advance, resolution;
			glm::vec4 uvs;
			float left, top;

            Glyph() {
            }
            ~Glyph() {
            }
    };
}

#endif //GLYPH_HPP
