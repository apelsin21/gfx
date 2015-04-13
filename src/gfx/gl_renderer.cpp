#include "gfx/gl_renderer.hpp"

gfx::GLRenderer::GLRenderer() {
    this->majorVersion = 3;
    this->minorVersion = 0;
    this->coreProfile = false;
    this->isDrawing = false;
    this->clearColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
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

bool gfx::GLRenderer::initialize(std::tuple<unsigned int, unsigned int> glVer, bool core) {
	return this->initialize(std::get<0>(glVer), std::get<1>(glVer), core);
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

    glEnable(GL_BLEND | GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void gfx::GLRenderer::setClearColor(const gfx::Color& c) {
    this->clearColor = c;
    glClearColor(this->clearColor.r,
                 this->clearColor.g,
                 this->clearColor.b,
                 this->clearColor.a);
}
gfx::Color gfx::GLRenderer::getClearColor() {
    return this->clearColor;
}

void gfx::GLRenderer::begin() {
    //We'll only draw if there's no other drawing going on. Don't want to mess with the state machine
    if(this->isDrawing) {
        return;
    }

    this->isDrawing = true;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void gfx::GLRenderer::end() {
    this->isDrawing = false;
}

void gfx::GLRenderer::drawText(const Font& f, const std::string& s, const glm::vec2& p) {
}
