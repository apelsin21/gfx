#include "sdl2window.hpp"

gfx::SDL2Window::SDL2Window() {
    this->_sdlWindowID = 0;
}
gfx::SDL2Window::~SDL2Window() {
    if(this->initialized)  { //deinitialize sdl2
        
        SDL_GL_DeleteContext(this->_sdlContext);
        
        if(this->_pSdlWindow != nullptr) {
            SDL_DestroyWindow(this->_pSdlWindow);
        }

        SDL_Quit();
    }
}

bool gfx::SDL2Window::initialize(const std::string& t, const glm::vec2& r) {
    if(this->initialized) {
        //do nothing if already initialized
        return false;
    }

    this->title = t;
    this->resolution = r;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Unable to initialize SDL:\n" << SDL_GetError() << "\n";
        this->initialized = false;
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    this->_pSdlWindow = SDL_CreateWindow(this->title.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            this->resolution.x, this->resolution.y,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(this->_pSdlWindow == nullptr) {
        std::cout << "Could not create SDL2 window:\n" << SDL_GetError() << "\n";
        this->initialized = false;
        return false;
    }

    this->_sdlContext = SDL_GL_CreateContext(this->_pSdlWindow);

    this->open = true;
    this->initialized = true;
    this->_sdlWindowID = SDL_GetWindowID(this->_pSdlWindow);
    this->_pSdlKeyboardState = SDL_GetKeyboardState(nullptr);

    return true;
}
bool gfx::SDL2Window::isInitialized() {
    return this->initialized;
}

std::string gfx::SDL2Window::getTitle() {
    if(!this->initialized) {
        return this->title;
    }
    
    SDL_PumpEvents();

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

    SDL_PumpEvents();

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
    
    SDL_PumpEvents();

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
    
    SDL_PumpEvents();

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

bool gfx::SDL2Window::isKeyPressed(gfx::KEYBOARD_KEY key) {
    if(!this->initialized) {
        return false;
    }
    
    SDL_PumpEvents();

    return this->_pSdlKeyboardState[convertKeyToSDLScancode(key)];
}

gfx::WINDOW_EVENT gfx::SDL2Window::pollEvents() {
    if(!this->initialized) {
        return gfx::WINDOW_EVENT::WINDOW_EVENT_NONE;
    }

    gfx::WINDOW_EVENT returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_NONE;

    while(SDL_PollEvent(&this->_sdlEvent)) {
        if(!this->_sdlEvent.type == SDL_WINDOWEVENT
                || !this->_sdlEvent.window.windowID == this->_sdlWindowID) {
            break;
        }

        switch(this->_sdlEvent.window.event) {
            case SDL_WINDOWEVENT_MOVED:
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_MOVED;
                break;
            case SDL_WINDOWEVENT_SHOWN:
                this->hidden = false;
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_SHOWN;
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                this->hidden = true;
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_HIDDEN;
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_EXPOSED;
                break;
            case SDL_WINDOWEVENT_RESIZED:
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_RESIZED;
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                this->maximized = false;
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_MINIMIZED;
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                this->maximized = true;
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_MAXIMIZED;
                break;
            case SDL_WINDOWEVENT_RESTORED:
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_RESTORED;
                break;
            case SDL_WINDOWEVENT_ENTER:
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_ENTER;
                break;
            case SDL_WINDOWEVENT_LEAVE:
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_LEAVE;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                this->focused = true;
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_FOCUS_GAINED;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                this->focused = false;
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_FOCUS_LOST;
                break;
            case SDL_WINDOWEVENT_CLOSE:
                this->open = false;
                returnEvent = gfx::WINDOW_EVENT::WINDOW_EVENT_CLOSE;
                break;
        }
    }
    
    return returnEvent;
}

void gfx::SDL2Window::swapBuffers() {
    if(!this->initialized) {
        return;
    }

    SDL_GL_SwapWindow(this->_pSdlWindow);
}
