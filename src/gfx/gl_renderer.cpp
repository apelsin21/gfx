#include "gfx/gl_renderer.hpp"

gfx::GLRenderer::GLRenderer() {
    this->majorVersion = 3;
    this->minorVersion = 0;
    this->clearColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
    this->resolution = glm::vec2(800, 600);

    this->coreProfile = false;
    this->isDrawing = false;
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
gfx::GLRenderer::~GLRenderer() {
    if(this->_sdlContext) {
        SDL_GL_DeleteContext(this->_sdlContext);
    }
    
    if(this->_pSdlWindow) {
        SDL_DestroyWindow(this->_pSdlWindow);
    }
    
    SDL_Quit();
}

std::tuple<unsigned int, unsigned int> gfx::GLRenderer::getSupportedGLVersion() {
    GLint supportedMajor, supportedMinor = 0;

    glGetIntegerv(GL_MAJOR_VERSION, &supportedMajor);
    glGetIntegerv(GL_MINOR_VERSION, &supportedMinor);

    return std::make_tuple((unsigned int)supportedMajor, (unsigned int)supportedMinor);
}

bool gfx::GLRenderer::isGLVersionSupported(unsigned int major, unsigned int minor) {
    std::tuple<unsigned int, unsigned int> supportedVersion = this->getSupportedGLVersion();

    if(major > std::get<0>(supportedVersion) || (major == std::get<0>(supportedVersion) && minor > std::get<1>(supportedVersion))) {
        return false;
    }

    return true;
}

bool gfx::GLRenderer::initialize(const std::string& t, unsigned int major, unsigned int minor, bool core) {
    if(this->initialized) {
        printf("renderer is already initialized!\n");
        return false;
    }

    if(!this->isGLVersionSupported(major, minor)) {
        printf("Failed to initialize GL renderer, unsupported GL version %d.%d\n", major, minor); 
        printf("Driver only supports OpenGL version: %d.%d\n", std::get<0>(this->getSupportedGLVersion()), std::get<1>(this->getSupportedGLVersion()));
        return false;
    }

    this->majorVersion = major;
    this->minorVersion = minor;
    this->coreProfile = core;

    this->title = t;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    this->_pSdlWindow = SDL_CreateWindow(this->title.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            (int)this->resolution.x, (int)this->resolution.y,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(!this->_pSdlWindow) {
        printf("Could not create SDL2 window: %s\n", SDL_GetError());
        return false;
    }

    this->_sdlContext = SDL_GL_CreateContext(this->_pSdlWindow);

    if(this->coreProfile) {
        glewExperimental = GL_TRUE;
    }

    GLenum err = glewInit();
    if(err != GLEW_OK) {
        printf("Err: %s\n", glewGetErrorString(err)); 
        printf("Failed to create a GL %d.%d context\n", major, minor);
        return false;
    }

    this->open = true;
    this->initialized = true;
    this->_sdlWindowID = SDL_GetWindowID(this->_pSdlWindow);
    this->_pSdlKeyboardState = SDL_GetKeyboardState(nullptr);

    glDepthFunc(GL_LESS);
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

std::string gfx::GLRenderer::getTitle() {
    return this->title;
}
bool gfx::GLRenderer::setTitle(const std::string& t) {
    this->title = t;

    if(this->initialized) {
        SDL_SetWindowTitle(this->_pSdlWindow, this->title.c_str());
        return true;
    }

    return false;
}

glm::vec2 gfx::GLRenderer::getResolution() {
    if(this->initialized) {
        int w, h = 0;
        SDL_GetWindowSize(this->_pSdlWindow, &w, &h);

        this->resolution = glm::vec2(w, h);
    }
    
    return this->resolution;
}
bool gfx::GLRenderer::setResolution(const glm::vec2& r) {
    this->resolution = r;

    if(this->initialized) {
        SDL_SetWindowSize(this->_pSdlWindow, (int)this->resolution.x, (int)this->resolution.y);
        return true;
    }

    return false;
}

glm::vec2 gfx::GLRenderer::getPosition() {
    if(this->initialized) {
        int x, y = 0;
        SDL_GetWindowPosition(this->_pSdlWindow, &x, &y);
        return glm::vec2(x, y);
    }

    return this->position;
}
bool gfx::GLRenderer::setPosition(const glm::vec2& p) {
    if(this->initialized) {
        SDL_SetWindowPosition(this->_pSdlWindow, (int)this->position.x, (int)this->position.y);
        return true;
    }

    return false;
}


bool gfx::GLRenderer::isOpen() {
    return this->open;
}
bool gfx::GLRenderer::close() {
    SDL_DestroyWindow(this->_pSdlWindow);

    this->open = false;
    return true;
}

bool gfx::GLRenderer::isFullscreen() {
    return this->fullscreen;
}
bool gfx::GLRenderer::setFullscreen(bool f) {
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
bool gfx::GLRenderer::setBorderlessFullscreen(bool f) {
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

bool gfx::GLRenderer::isMaximized() {
    return this->maximized;
}
bool gfx::GLRenderer::setMaximized(bool m) {
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

bool gfx::GLRenderer::isHidden() {
    return this->hidden;
}
bool gfx::GLRenderer::setHidden(bool h) {
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

bool gfx::GLRenderer::isFocused() {
    if(!this->initialized) {
        return false;
    }

    if(SDL_GetWindowGrab(this->_pSdlWindow) == SDL_TRUE) {
        return true;
    } else {
        return false;
    }
}
bool gfx::GLRenderer::setFocused(bool f) {
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

bool gfx::GLRenderer::isKeyPressed(core::KEYBOARD_KEY key) {
    return this->_pSdlKeyboardState[convertKeyToSDLScancode(key)];
}

gfx::RENDERER_EVENT gfx::GLRenderer::pollEvents() {
    if(!this->initialized) {
        return gfx::RENDERER_EVENT::RENDERER_EVENT_NONE;
    }

    gfx::RENDERER_EVENT returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_NONE;

    while(SDL_PollEvent(&this->_sdlEvent)) {
        if(this->_sdlEvent.type != SDL_WINDOWEVENT || this->_sdlEvent.window.windowID != this->_sdlWindowID) {
            break;
        }

        switch(this->_sdlEvent.window.event) {
            case SDL_WINDOWEVENT_MOVED:
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_MOVED;
                break;
            case SDL_WINDOWEVENT_SHOWN:
                this->hidden = false;
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_SHOWN;
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                this->hidden = true;
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_HIDDEN;
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_EXPOSED;
                break;
            case SDL_WINDOWEVENT_RESIZED:
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_RESIZED;
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_RESIZED;
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                this->maximized = false;
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_MINIMIZED;
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                this->maximized = true;
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_MAXIMIZED;
                break;
            case SDL_WINDOWEVENT_RESTORED:
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_RESTORED;
                break;
            case SDL_WINDOWEVENT_ENTER:
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_ENTER;
                break;
            case SDL_WINDOWEVENT_LEAVE:
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_LEAVE;
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                this->focused = true;
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_FOCUS_GAINED;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                this->focused = false;
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_FOCUS_LOST;
                break;
            case SDL_WINDOWEVENT_CLOSE:
                this->close();
                returnEvent = gfx::RENDERER_EVENT::RENDERER_EVENT_CLOSE;
                break;
            default:
                break;
        }
    }
    
    return returnEvent;
}

std::string gfx::GLRenderer::getClipboardString() {
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
bool gfx::GLRenderer::setClipboardString(const std::string& s) {
    if(!this->initialized) {
        return false;
    } else if(SDL_SetClipboardText(s.c_str()) < 0) {
        printf("failed to set clipboard text, err: %s\n", SDL_GetError());

        return false;
    }

    return true;
}

SDL_Scancode gfx::GLRenderer::convertKeyToSDLScancode(core::KEYBOARD_KEY gfxKey) {
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

void gfx::GLRenderer::swapBuffers() {
    if(!this->initialized) {
        return;
    }

    SDL_GL_SwapWindow(this->_pSdlWindow);
}
