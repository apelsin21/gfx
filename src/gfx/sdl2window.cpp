#include "sdl2window.hpp"

gfx::SDL2Window::SDL2Window() {
}
gfx::SDL2Window::~SDL2Window() {
    SDL_Quit();
}

void gfx::SDL2Window::initialize() {
    SDL_Init(SDL_INIT_VIDEO);
    this->initialized = true;
}
bool gfx::SDL2Window::isInitialized() {
    return this->initialized;
}

std::string gfx::SDL2Window::getTitle() {
    return this->title;
}
bool gfx::SDL2Window::setTitle(const std::string& t) {
}

glm::vec2 gfx::SDL2Window::getResolution() {
    return this->resolution;
}
bool gfx::SDL2Window::setResolution(const glm::vec2& r) {
}

glm::vec2 gfx::SDL2Window::getPosition() {
}
bool gfx::SDL2Window::setPosition(const glm::vec2& p) {
}

bool gfx::SDL2Window::isOpen() {
    return this->open;
}
bool gfx::SDL2Window::setOpen(bool o) {
}

bool gfx::SDL2Window::isFullscreen() {
    return this->fullscreen;
}
bool gfx::SDL2Window::setFullscreen(bool f) {
}

bool gfx::SDL2Window::isMaximized() {
    return this->maximized;
}
bool gfx::SDL2Window::setMaximized(bool m) {
}

bool gfx::SDL2Window::isHidden() {
    return this->hidden;
}
bool gfx::SDL2Window::setHidden(bool h) {
}

bool gfx::SDL2Window::isFocused() {
    return this->focused;
}
bool gfx::SDL2Window::setFocused(bool f) {
}

void gfx::SDL2Window::swapBuffers() {
}
