#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>

#include <glm/glm.hpp>

#include "gfx/font.hpp"

namespace gfx {
    class Renderer {
        protected:
            bool isDrawing;
        public:
            virtual bool initialize(unsigned int, unsigned int, bool) = 0;

            virtual void begin() = 0;
            virtual void drawText(const gfx::Font&, const std::string&, const glm::vec2&) = 0;
            virtual void end() = 0;
    };
}

#endif //RENDERER_HPP
