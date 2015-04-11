#include "gfx/opengl_renderer.hpp"

gfx::OpenGLRenderer::OpenGLRenderer() {
    this->majorVersion = 3;
    this->minorVersion = 0;
    this->coreProfile = false;
    this->isDrawing = false;
}
gfx::OpenGLRenderer::~OpenGLRenderer() {
}

bool gfx::OpenGLRenderer::initialize(unsigned int major, unsigned int minor, bool core) {
    //Nothing
}

void gfx::OpenGLRenderer::begin() {
    //If it's already drawing, we won't do it again!
    if(this->isDrawing) {
        return;
    }

    this->isDrawing = true;
}
void gfx::OpenGLRenderer::end() {
    this->isDrawing = false;
}

void gfx::OpenGLRenderer::drawText(const Font& f, const std::string& s, const glm::vec2& p) {
    //Nothing
}
