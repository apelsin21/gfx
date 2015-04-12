#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

#include "gfx/color.hpp"
#include "gfx/renderer.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <iostream>
#include <tuple>

namespace gfx {
    class GLRenderer : public Renderer {
        protected:
            Color clearColor;
        public:
            unsigned int majorVersion, minorVersion;
            bool coreProfile;

            GLRenderer();
            ~GLRenderer();

            void setClearColor(const Color&);
            Color getClearColor();

            std::tuple<GLint, GLint> getSupportedGLVersion();
            bool isGLVersionSupported(unsigned int, unsigned int);

            bool initialize(unsigned int, unsigned int, bool);

            void begin();
            void drawText(const Font&, const std::string&, const glm::vec2&);
            void end();
    };
}

#endif //OPENGL_RENDERER_HPP
