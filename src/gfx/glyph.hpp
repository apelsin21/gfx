#ifndef GLYPH_HPP
#define GLYPH_HPP

#include <glm/glm.hpp>

namespace gfx {
    class Glyph {
        public:
            glm::vec2 res, advance;
            float left, top, offset;

            Glyph(const glm::vec2& r, const glm::vec2 a, float l, float t, float o) {
                this->res = r;
                this->advance = a;
                this->left = l;
                this->top = t;
                this->offset = o;
            }
            Glyph() {
                this->left = 0.0f;
                this->top = 0.0f;
                this->offset = 0.0f;
            }
            ~Glyph() {
            }
    };
}

#endif //GLYPH_HPP
