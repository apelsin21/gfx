#include "core/window.hpp"

mg::Window::Window() {
	this->settings = mg::ContextSettings(3, 3, 24, true, true, true);

	this->open = false;
	this->fullscreen = false;
	this->initialized = false;
	this->maximized = false;
	this->hidden = false;
	this->focused = false;

	this->width = 0;
	this->height = 0;
	this->x = 0;
	this->y = 0;
}
