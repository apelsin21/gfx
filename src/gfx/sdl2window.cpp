#include "sdl2window.hpp"

gfx::SDL2Window::SDL2Window() {
}
gfx::SDL2Window::~SDL2Window() {
    if(this->initialized)  { //deinitialize sdl2
        
        if(this->_pSdlWindow != nullptr) {
            SDL_DestroyWindow(this->_pSdlWindow);
        }

        SDL_Quit();
    }
}

bool gfx::SDL2Window::initialize(const std::string& t, const glm::vec2& r) {
    if(this->initialized) {
        //Do nothing if already initialized
        return false;
    }

    this->title = t;
    this->resolution = r;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Unable to initialize SDL:\n" << SDL_GetError() << "\n";
        this->initialized = false;
        return false;
    }

    this->_pSdlWindow = SDL_CreateWindow(this->title.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            this->resolution.x, this->resolution.y,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(this->_pSdlWindow == nullptr) {
        std::cout << "Could not create SDL2 window:\n" << SDL_GetError() << "\n";
        this->initialized = false;
        return false;
    }

    this->open = true;
    this->initialized = true;
    
    return true;
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
    if(!this->initialized) {
        return this->position;
    }

    int x = 0, y = 0;
    SDL_GetWindowPosition(this->_pSdlWindow, &x, &y);

    this->position = glm::vec2(x, y);

    return this->position;
}
bool gfx::SDL2Window::setPosition(const glm::vec2& p) {
    if(!this->initialized) {
        return false;
    }

    SDL_SetWindowPosition(this->_pSdlWindow, (int)this->position.x, (int)this->position.y);

    return true;
}

bool gfx::SDL2Window::isOpen() {
    return this->open;
}
bool gfx::SDL2Window::close() {
    if(this->initialized) {
        this->open = false;
        return false;
    }

    SDL_DestroyWindow(this->_pSdlWindow);

    this->open = false;
    return true;
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
