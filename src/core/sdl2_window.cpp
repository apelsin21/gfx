#include "sdl2_window.hpp"

core::SDL2Window::SDL2Window() {
    this->open = false;
    this->fullscreen = false;
    this->initialized = false;
    this->maximized = false;
    this->hidden = false;
    this->focused = false;

    this->_sdlWindowID = 0;
    this->_sdlContext = NULL;
    this->_pSdlWindow = nullptr;
}
core::SDL2Window::~SDL2Window() {
    if(this->_sdlContext) {
        SDL_GL_DeleteContext(this->_sdlContext);
    }
    
    if(this->_pSdlWindow) {
        SDL_DestroyWindow(this->_pSdlWindow);
    }
    
    SDL_Quit();
}

bool core::SDL2Window::initialize(const std::string& t, const glm::vec2& r) {
    if(this->initialized) {
        std::cout << "window is already initialized!\n";
        return false;
    }

    this->title = t;
    this->resolution = r;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Unable to initialize SDL:\n" << SDL_GetError() << "\n";
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

    if(!this->_pSdlWindow) {
        std::cout << "Could not create SDL2 window:\n" << SDL_GetError() << "\n";
        return false;
    }

    this->_sdlContext = SDL_GL_CreateContext(this->_pSdlWindow);

    this->open = true;
    this->initialized = true;
    this->_sdlWindowID = SDL_GetWindowID(this->_pSdlWindow);
    this->_pSdlKeyboardState = SDL_GetKeyboardState(nullptr);

    return true;
}

std::string core::SDL2Window::getTitle() {
    this->title = std::string(SDL_GetWindowTitle(this->_pSdlWindow));

    return this->title;
}
bool core::SDL2Window::setTitle(const std::string& t) {
    this->title = t;

    if(this->initialized) {
        SDL_SetWindowTitle(this->_pSdlWindow, this->title.c_str());
        return true;
    }

    return false;
}

glm::vec2 core::SDL2Window::getResolution() {
    if(this->initialized) {
        int w, h = 0;
        SDL_GetWindowSize(this->_pSdlWindow, &w, &h);

        this->resolution = glm::vec2(w, h);
    }
    
    return this->resolution;
}
bool core::SDL2Window::setResolution(const glm::vec2& r) {
    this->resolution = r;

    if(this->initialized) {
        SDL_SetWindowSize(this->_pSdlWindow, (int)this->resolution.x, (int)this->resolution.y);
        return true;
    }

    return false;
}

glm::vec2 core::SDL2Window::getPosition() {
    if(this->initialized) {
        int x, y = 0;
        SDL_GetWindowPosition(this->_pSdlWindow, &x, &y);
        return glm::vec2(x, y);
    }

    return this->position;
}
bool core::SDL2Window::setPosition(const glm::vec2& p) {
    if(this->initialized) {
        SDL_SetWindowPosition(this->_pSdlWindow, (int)this->position.x, (int)this->position.y);
        return true;
    }

    return false;
}

bool core::SDL2Window::isOpen() {
    return this->open;
}
bool core::SDL2Window::close() {
    SDL_DestroyWindow(this->_pSdlWindow);

    this->open = false;
    return true;
}

bool core::SDL2Window::isFullscreen() {
    return this->fullscreen;
}
bool core::SDL2Window::setFullscreen(bool f) {
    if(!this->initialized) {
        return false;
    } else if(f) {
        if(SDL_SetWindowFullscreen(this->_pSdlWindow, SDL_WINDOW_FULLSCREEN) < 0) {
            return false;
        }
    } else {
        if(SDL_SetWindowFullscreen(this->_pSdlWindow, 0) < 0) {
            return false;
        }
    }

    return true;
}
bool core::SDL2Window::setBorderlessFullscreen(bool f) {
    this->fullscreen = f;

    if(!this->initialized) {
        return false;
    } else if(this->fullscreen) {
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

bool core::SDL2Window::isMaximized() {
    return this->maximized;
}
bool core::SDL2Window::setMaximized(bool m) {
    this->maximized = m;

    if(!this->initialized) {
        return false;
    } else if(this->maximized) {
        SDL_MaximizeWindow(this->_pSdlWindow);
    } else {
        SDL_RestoreWindow(this->_pSdlWindow);
    }

    return true;
}

bool core::SDL2Window::isHidden() {
    return this->hidden;
}
bool core::SDL2Window::setHidden(bool h) {
    this->hidden = h;
    
    if(!this->initialized) {
        return false; 
    } else if(this->hidden) {
        SDL_HideWindow(this->_pSdlWindow);
    } else {
        SDL_ShowWindow(this->_pSdlWindow);
    }

    return true;
}

bool core::SDL2Window::isFocused() {
    if(!this->initialized) {
        return false;
    }

    if(SDL_GetWindowGrab(this->_pSdlWindow) == SDL_TRUE) {
        return true;
    } else {
        return false;
    }
}
bool core::SDL2Window::setFocused(bool f) {
    this->focused = f;

    if(!this->initialized) {
        return false;
    } else if(this->focused) {
        SDL_SetWindowGrab(this->_pSdlWindow, SDL_TRUE);
    } else {
        SDL_SetWindowGrab(this->_pSdlWindow, SDL_FALSE);
    }

    return true;
}

bool core::SDL2Window::isKeyPressed(core::KEYBOARD_KEY key) {
    return this->_pSdlKeyboardState[convertKeyToSDLScancode(key)];
}

core::WINDOW_EVENT core::SDL2Window::pollEvents() {
    if(!this->initialized) {
        return core::WINDOW_EVENT::WINDOW_EVENT_NONE;
    }

    core::WINDOW_EVENT returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_NONE;

    while(SDL_PollEvent(&this->_sdlEvent)) {
        if(this->_sdlEvent.type != SDL_WINDOWEVENT || this->_sdlEvent.window.windowID != this->_sdlWindowID) {
            break;
        }

        switch(this->_sdlEvent.window.event) {
            case SDL_WINDOWEVENT_MOVED:
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_MOVED;
                break;
            case SDL_WINDOWEVENT_SHOWN:
                this->hidden = false;
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_SHOWN;
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                this->hidden = true;
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_HIDDEN;
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_EXPOSED;
                break;
            case SDL_WINDOWEVENT_RESIZED:
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_RESIZED;
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_RESIZED;
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                this->maximized = false;
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_MINIMIZED;
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                this->maximized = true;
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_MAXIMIZED;
                break;
            case SDL_WINDOWEVENT_RESTORED:
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_RESTORED;
                break;
            case SDL_WINDOWEVENT_ENTER:
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_ENTER;
                break;
            case SDL_WINDOWEVENT_LEAVE:
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_LEAVE;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                this->focused = true;
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_FOCUS_GAINED;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                this->focused = false;
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_FOCUS_LOST;
                break;
            case SDL_WINDOWEVENT_CLOSE:
                this->close();
                returnEvent = core::WINDOW_EVENT::WINDOW_EVENT_CLOSE;
                break;
            default:
                break;
        }
    }
    
    return returnEvent;
}

std::string core::SDL2Window::getClipboardString() {
    std::string returnval;

    if(!this->initialized) {
    } else if(SDL_HasClipboardText() == SDL_TRUE) {
        //Because this needs to be manually freed
        char* temp_clip = SDL_GetClipboardText();

        returnval = temp_clip;

        free(temp_clip);
    }

    return returnval;
}
bool core::SDL2Window::setClipboardString(const std::string& s) {
    if(!this->initialized) {
        return false;
    } else if(SDL_SetClipboardText(s.c_str()) < 0) {
        std::cout << "failed to set clipboard text, err:\n"; 
        std::cout << SDL_GetError() << "\n";

        return false;
    }

    return true;
}

SDL_Scancode core::SDL2Window::convertKeyToSDLScancode(core::KEYBOARD_KEY gfxKey) {
    SDL_Scancode sdlKey = SDL_SCANCODE_UNKNOWN;

    switch(gfxKey) {
        case core::KEYBOARD_KEY::KEY_A:
            sdlKey = SDL_SCANCODE_A;
            break;
        case core::KEYBOARD_KEY::KEY_B:
            sdlKey = SDL_SCANCODE_B;
            break;
        case core::KEYBOARD_KEY::KEY_C:
            sdlKey = SDL_SCANCODE_C;
            break;
        case core::KEYBOARD_KEY::KEY_D:
            sdlKey = SDL_SCANCODE_D;
            break;
        case core::KEYBOARD_KEY::KEY_E:
            sdlKey = SDL_SCANCODE_E;
            break;
        case core::KEYBOARD_KEY::KEY_F:
            sdlKey = SDL_SCANCODE_F;
            break;
        case core::KEYBOARD_KEY::KEY_G:
            sdlKey = SDL_SCANCODE_G;
            break;
        case core::KEYBOARD_KEY::KEY_H:
            sdlKey = SDL_SCANCODE_H;
            break;
        case core::KEYBOARD_KEY::KEY_I:
            sdlKey = SDL_SCANCODE_I;
            break;
        case core::KEYBOARD_KEY::KEY_J:
            sdlKey = SDL_SCANCODE_J;
            break;
        case core::KEYBOARD_KEY::KEY_K:
            sdlKey = SDL_SCANCODE_K;
            break;
        case core::KEYBOARD_KEY::KEY_L:
            sdlKey = SDL_SCANCODE_L;
            break;
        case core::KEYBOARD_KEY::KEY_M:
            sdlKey = SDL_SCANCODE_M;
            break;
        case core::KEYBOARD_KEY::KEY_N:
            sdlKey = SDL_SCANCODE_N;
            break;
        case core::KEYBOARD_KEY::KEY_O:
            sdlKey = SDL_SCANCODE_O;
            break;
        case core::KEYBOARD_KEY::KEY_P:
            sdlKey = SDL_SCANCODE_P;
            break;
        case core::KEYBOARD_KEY::KEY_Q:
            sdlKey = SDL_SCANCODE_Q;
            break;
        case core::KEYBOARD_KEY::KEY_R:
            sdlKey = SDL_SCANCODE_R;
            break;
        case core::KEYBOARD_KEY::KEY_S:
            sdlKey = SDL_SCANCODE_S;
            break;
        case core::KEYBOARD_KEY::KEY_T:
            sdlKey = SDL_SCANCODE_T;
            break;
        case core::KEYBOARD_KEY::KEY_U:
            sdlKey = SDL_SCANCODE_U;
            break;
        case core::KEYBOARD_KEY::KEY_V:
            sdlKey = SDL_SCANCODE_V;
            break;
        case core::KEYBOARD_KEY::KEY_W:
            sdlKey = SDL_SCANCODE_W;
            break;
        case core::KEYBOARD_KEY::KEY_X:
            sdlKey = SDL_SCANCODE_X;
            break;
        case core::KEYBOARD_KEY::KEY_Y:
            sdlKey = SDL_SCANCODE_Y;
            break;
        case core::KEYBOARD_KEY::KEY_Z:
            sdlKey = SDL_SCANCODE_Z;
            break;
        
        case core::KEYBOARD_KEY::KEY_ESCAPE:
            sdlKey = SDL_SCANCODE_ESCAPE;
            break;

        case core::KEYBOARD_KEY::KEY_F1:
            sdlKey = SDL_SCANCODE_F1;
            break;
        case core::KEYBOARD_KEY::KEY_F2:
            sdlKey = SDL_SCANCODE_F2;
            break;
        case core::KEYBOARD_KEY::KEY_F3:
            sdlKey = SDL_SCANCODE_F3;
            break;
        case core::KEYBOARD_KEY::KEY_F4:
            sdlKey = SDL_SCANCODE_F4;
            break;
        case core::KEYBOARD_KEY::KEY_F5:
            sdlKey = SDL_SCANCODE_F5;
            break;
        case core::KEYBOARD_KEY::KEY_F6:
            sdlKey = SDL_SCANCODE_F6;
            break;
        case core::KEYBOARD_KEY::KEY_F7:
            sdlKey = SDL_SCANCODE_F7;
            break;
        case core::KEYBOARD_KEY::KEY_F8:
            sdlKey = SDL_SCANCODE_F8;
            break;
        case core::KEYBOARD_KEY::KEY_F9:
            sdlKey = SDL_SCANCODE_F9;
            break;
        case core::KEYBOARD_KEY::KEY_F10:
            sdlKey = SDL_SCANCODE_F10;
            break;
        case core::KEYBOARD_KEY::KEY_F11:
            sdlKey = SDL_SCANCODE_F11;
            break;
        case core::KEYBOARD_KEY::KEY_F12:
            sdlKey = SDL_SCANCODE_F12;
            break;
        default:
            break;
    }

    return sdlKey;
}

void core::SDL2Window::swapBuffers() {
    if(!this->initialized) {
        return;
    }

    SDL_GL_SwapWindow(this->_pSdlWindow);
}
