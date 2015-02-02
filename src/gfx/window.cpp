#include "gfx/window.hpp"

gfx::Window::Window() {
    this->open = false;
    this->fullscreen = false;
    this->maximized = false;
    this->hidden = false;
    this->focused = false;
    this->initialized = false;
}
gfx::Window::~Window() {
}
