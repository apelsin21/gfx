#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

#include "gfx/color.hpp"
#include "gfx/renderer.hpp"

namespace gfx {
    class OpenGLRenderer : public Renderer {
        protected:
            Color clearColor;
        public:
            unsigned int majorVersion, minorVersion;
            bool coreProfile;

            OpenGLRenderer();
            ~OpenGLRenderer();

            void setColor(const Color&);
            Color getColor();

            bool initialize(unsigned int, unsigned int, bool);

            void begin();
            void drawText(const Font&, const std::string&, const glm::vec2&);
            void end();
    };
}

#endif //OPENGL_RENDERER_HPP
