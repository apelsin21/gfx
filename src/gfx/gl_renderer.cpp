#include "gfx/gl_renderer.hpp"

gfx::GLRenderer::GLRenderer() {
    this->majorVersion = 3;
    this->minorVersion = 0;
    this->coreProfile = false;
    this->isDrawing = false;
}
gfx::GLRenderer::~GLRenderer() {
}

std::tuple<GLint, GLint> gfx::GLRenderer::getSupportedGLVersion() {
    GLint supportedMajor, supportedMinor = 0;

    glGetIntegerv(GL_MAJOR_VERSION, &supportedMajor);
    glGetIntegerv(GL_MINOR_VERSION, &supportedMinor);

    return std::make_tuple(supportedMajor, supportedMinor);
}

bool gfx::GLRenderer::isGLVersionSupported(unsigned int major, unsigned int minor) {
    std::tuple<GLint, GLint> supportedVersion = this->getSupportedGLVersion();

    if(major < std::get<0>(supportedVersion) && minor < std::get<1>(supportedVersion)) {
        return false;
    }
    
    return true;
}

bool gfx::GLRenderer::initialize(unsigned int major, unsigned int minor, bool core) {
    if(!this->isGLVersionSupported(major, minor)) {
        std::cout << "Failed to initialize GL renderer, unsupported GL version " << major << "." << minor << "\n";
        return false;
    }

    if(core) {
        glewExperimental = GL_TRUE;
    }

    GLenum err = glewInit();
    if(err != GLEW_OK) {
        std::cout << "Err: " << glewGetErrorString(err) << "\n"; 
        std::cout << "Failed to create a GL " << major << "." << minor << " core=" << core << " context\n";
        return false;
    }

    this->majorVersion = major;
    this->minorVersion = minor;
    this->coreProfile = core;

    return true;
}

void gfx::GLRenderer::begin() {
    //If it's already drawing, we won't do it again!
    if(this->isDrawing) {
        return;
    }

    this->isDrawing = true;
}
void gfx::GLRenderer::end() {
    this->isDrawing = false;
}

void gfx::GLRenderer::drawText(const Font& f, const std::string& s, const glm::vec2& p) {
    //Nothing
}
