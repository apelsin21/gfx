#include "core/window.hpp"

core::Window::Window() {
    this->open = false;
    this->fullscreen = false;
    this->maximized = false;
    this->hidden = false;
    this->focused = false;
    this->initialized = false;
}
core::Window::~Window() {
}
