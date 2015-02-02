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
    if(!this->initialized) {
        return this->title;
    }

    this->title = std::string(SDL_GetWindowTitle(this->_pSdlWindow));

    return this->title;
}
bool gfx::SDL2Window::setTitle(const std::string& t) {
    if(!this->initialized) {
        return false;
    }

    this->title = t;

    SDL_SetWindowTitle(this->_pSdlWindow, this->title.c_str());

    return true;
}

glm::vec2 gfx::SDL2Window::getResolution() {
    if(!this->initialized) {
        return this->resolution;
    }
    

    int w = 0, h = 0;
    SDL_GetWindowSize(this->_pSdlWindow, &w, &h);

    this->resolution = glm::vec2(w, h);
    
    return this->resolution;
}
bool gfx::SDL2Window::setResolution(const glm::vec2& r) {
    if(!this->initialized) {
        return false;
    }

    this->resolution = r;

    SDL_SetWindowSize(this->_pSdlWindow, (int)this->resolution.x, (int)this->resolution.y);

    return true;
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
    if(!this->initialized) {
        return false;
    }
    
    this->fullscreen = f;

    if(this->fullscreen) {
        //set window fullscreen
        if(SDL_SetWindowFullscreen(this->_pSdlWindow, SDL_WINDOW_FULLSCREEN) < 0) {
            return false;
        }
    } else {
        //set window to windowed mode
        if(SDL_SetWindowFullscreen(this->_pSdlWindow, 0) < 0) {
            return false;
        }
    }

    return true;
}
bool gfx::SDL2Window::setBorderlessFullscreen(bool f) {
    if(!this->initialized) {
        return false;
    }
    
    this->fullscreen = f;

    if(this->fullscreen) {
        //set window to borderless fullscreen
        if(SDL_SetWindowFullscreen(this->_pSdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0) {
            return false;
        }
    } else {
        //set window to windowed mode
        if(SDL_SetWindowFullscreen(this->_pSdlWindow, 0) < 0) {
            return false;
        }
    }

    return true;
}

bool gfx::SDL2Window::isMaximized() {
    return this->maximized;
}
bool gfx::SDL2Window::setMaximized(bool m) {
    if(!this->initialized) {
        return false;
    }
    
    this->maximized = m;

    if(this->maximized) {
        //maximize window
        SDL_MaximizeWindow(this->_pSdlWindow);
    } else {
        //restore window
        SDL_RestoreWindow(this->_pSdlWindow);
    }

    return true;
}

bool gfx::SDL2Window::isHidden() {
    return this->hidden;
}
bool gfx::SDL2Window::setHidden(bool h) {
    if(!this->initialized) {
        return false;
    }

    this->hidden = h;

    if(this->hidden) {
        //hides window
        SDL_HideWindow(this->_pSdlWindow);
    } else {
        //shows window
        SDL_ShowWindow(this->_pSdlWindow);
    }

    return true;
}

bool gfx::SDL2Window::isFocused() {
    if(!this->initialized) {
        return this->focused;
    }

    if(SDL_GetWindowGrab(this->_pSdlWindow) == SDL_TRUE) {
        return true;
    } else {
        return false;
    }
}
bool gfx::SDL2Window::setFocused(bool f) {
    if(!this->initialized) {
        return false;
    }

    this->focused = f;

    if(this->focused) {
        SDL_SetWindowGrab(this->_pSdlWindow, SDL_TRUE);
    } else {
        SDL_SetWindowGrab(this->_pSdlWindow, SDL_FALSE);
    }

    return true;
}

void gfx::SDL2Window::swapBuffers() {
    if(!this->initialized) {
        return;
    }

    SDL_GL_SwapWindow(this->_pSdlWindow);
}
