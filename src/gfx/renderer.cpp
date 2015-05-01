#include "gfx/renderer.hpp"

gfx::Renderer::Renderer() {
    this->clearColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
    this->resolution = glm::i32vec2(800, 600);

    this->isDrawing = false;
    this->open = false;
    this->fullscreen = false;
    this->initialized = false;
    this->maximized = false;
    this->hidden = false;
    this->focused = false;
	this->boundTextureID = 0;
	this->boundShaderProgramID = 0;

    this->_sdlWindowID = 0;
    this->_sdlContext = NULL;
    this->_pSdlWindow = nullptr;
}
gfx::Renderer::~Renderer() {
    if(this->_sdlContext) {
        SDL_GL_DeleteContext(this->_sdlContext);
    }
    
    if(this->_pSdlWindow) {
        SDL_DestroyWindow(this->_pSdlWindow);
    }
    
    SDL_Quit();
}

bool gfx::Renderer::initialize(const std::string& t, const glm::i32vec2& res, ContextSettings& context) {
    if(this->initialized) {
        throw std::runtime_error("renderer is already initialized!\n");
        return false;
    }

    this->contextSettings = context;
    this->resolution = res;
    this->title = t;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::string errMsg("Unable to initialize SDL\n");
        errMsg += SDL_GetError();
        errMsg += "\n";
        throw std::runtime_error(errMsg);
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, this->contextSettings.major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, this->contextSettings.minor);

    if(this->contextSettings.doubleBuffered) {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    } else {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
    }

    if(this->contextSettings.coreProfile) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);                                                                                                          
	}

	if(this->contextSettings.vsync) {
		SDL_GL_SetSwapInterval(1);
	} else {
		SDL_GL_SetSwapInterval(0);
	}

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, this->contextSettings.depthBits);

    this->_pSdlWindow = SDL_CreateWindow(this->title.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            res.x, res.y,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(!this->_pSdlWindow) {
        std::string errMsg("Could not create SDL2 window, error:\n");
        errMsg += SDL_GetError();
        errMsg += "\n";
        throw std::runtime_error(errMsg);
        return false;
    }

    this->_sdlContext = SDL_GL_CreateContext(this->_pSdlWindow);

    if(this->contextSettings.coreProfile) {
        glewExperimental = GL_TRUE;
    }

    GLenum err = glewInit();
    if(err != GLEW_OK) {
        std::string errMsg("failed to initialize GLEW, error:\n");
        errMsg += (char*)glewGetErrorString(err);
        throw std::runtime_error(errMsg);
        return false;
    }

    this->open = true;
    this->initialized = true;
    this->_sdlWindowID = SDL_GetWindowID(this->_pSdlWindow);
    this->_pSdlKeyboardState = SDL_GetKeyboardState(nullptr);

    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void gfx::Renderer::setClearColor(const gfx::Color& c) {
	if(!this->initialized) {
		printf("tried to set clearcolor of uninitialized renderer.\n");
		return;
	}

    this->clearColor = c;
    glClearColor(c.r,
                 c.g,
                 c.b,
                 c.a);
}
gfx::Color gfx::Renderer::getClearColor() {
    return this->clearColor;
}

std::string gfx::Renderer::getTitle() {
    return this->title;
}
bool gfx::Renderer::setTitle(const std::string& t) {
    if(this->initialized) {
    	this->title = t;
        SDL_SetWindowTitle(this->_pSdlWindow, this->title.c_str());
        return true;
    }

    return false;
}

glm::i32vec2 gfx::Renderer::getResolution() {
    return this->resolution;
}
bool gfx::Renderer::setResolution(const glm::i32vec2& r) {
    if(this->initialized) {
		this->resolution = r;
        SDL_SetWindowSize(this->_pSdlWindow, this->resolution.x, this->resolution.y);
        return true;
    }

    return false;
}

glm::i32vec2 gfx::Renderer::getPosition() {
    return this->position;
}
bool gfx::Renderer::setPosition(const glm::i32vec2& p) {
    if(this->initialized) {
		this->position = p;
        SDL_SetWindowPosition(this->_pSdlWindow, p.x, p.y);
        return true;
    }

    return false;
}

bool gfx::Renderer::isOpen() {
    return this->open;
}
void gfx::Renderer::close() {
    this->open = false;
}

bool gfx::Renderer::isFullscreen() {
    return this->fullscreen;
}
void gfx::Renderer::setFullscreen() {
    if(!this->initialized) {
        throw std::runtime_error("tried to set uninitialized renderer to fullscreen.\n");
    }

    if(SDL_SetWindowFullscreen(this->_pSdlWindow, SDL_WINDOW_FULLSCREEN) < 0) {
        throw std::runtime_error("failed to set renderer to fullscreen.\n");
    } else {
        this->fullscreen = true;
    }
}
void gfx::Renderer::setBorderlessFullscreen() {
    if(!this->initialized) {
        throw std::runtime_error("tried to set uninitialized renderer to borderless fullscreen!\n");
    }

    if(SDL_SetWindowFullscreen(this->_pSdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0) {
        throw std::runtime_error("failed to set renderer to borderless fullscreen!\n");
    } else {
        this->fullscreen = true;
    }
}
void gfx::Renderer::setWindowed() {
    if(!this->initialized) {
        throw std::runtime_error("tried to set uninitialized renderer to windowed mode.\n");
    }    

    if(SDL_SetWindowFullscreen(this->_pSdlWindow, 0) < 0) {
        throw std::runtime_error("failed to set renderer to windowed mode.\n");
    } else {
        this->fullscreen = false;
    }
}

bool gfx::Renderer::isMaximized() {
    return this->maximized;
}
bool gfx::Renderer::setMaximized(bool m) {
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

bool gfx::Renderer::isHidden() {
    return this->hidden;
}
bool gfx::Renderer::setHidden(bool h) {
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

bool gfx::Renderer::isFocused() {
	return this->focused;
}
bool gfx::Renderer::setFocused(bool f) {
    if(!this->initialized) {
        return false;
    }

	if(f) {
        SDL_SetWindowGrab(this->_pSdlWindow, SDL_TRUE);
    	this->focused = true;
    } else {
        SDL_SetWindowGrab(this->_pSdlWindow, SDL_FALSE);
    }

    return true;
}

bool gfx::Renderer::isKeyPressed(core::KEYBOARD_KEY key) {
    return this->_pSdlKeyboardState[convertKeyToSDLScancode(key)];
}

void gfx::Renderer::pollEvents() {
    while(SDL_PollEvent(&this->_sdlEvent) && this->_sdlEvent.type == SDL_WINDOWEVENT && this->_sdlEvent.window.windowID == this->_sdlWindowID) {
        switch(this->_sdlEvent.window.event) {
            case SDL_WINDOWEVENT_MOVED:
                break;

            case SDL_WINDOWEVENT_SHOWN:
                this->hidden = false;
                break;

            case SDL_WINDOWEVENT_HIDDEN:
                this->hidden = true;
                break;
				 
            case SDL_WINDOWEVENT_EXPOSED:
                break;

            case SDL_WINDOWEVENT_RESIZED:
				this->resolution = glm::i32vec2(this->_sdlEvent.window.data1, this->_sdlEvent.window.data2);
				glViewport(0, 0, this->_sdlEvent.window.data1, this->_sdlEvent.window.data2);
                break;

            case SDL_WINDOWEVENT_MINIMIZED:
                this->maximized = false;
                break;

            case SDL_WINDOWEVENT_MAXIMIZED:
                this->maximized = true;
                break;
				 
            case SDL_WINDOWEVENT_RESTORED:
                break;

            case SDL_WINDOWEVENT_ENTER:
                break;

            case SDL_WINDOWEVENT_LEAVE:
                break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
                this->focused = true;
                break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
                this->focused = false;
                break;

            case SDL_WINDOWEVENT_CLOSE:
                this->close();
                break;

            default:
                break;
        }
    }
}

std::string gfx::Renderer::getClipboardString() {
    std::string returnval;

    if(this->initialized && SDL_HasClipboardText() == SDL_TRUE) {
        //Because this needs to be manually freed
        char* temp_clip = SDL_GetClipboardText();

        returnval = temp_clip;

        free(temp_clip);
    }

    return returnval;
}
bool gfx::Renderer::setClipboardString(const std::string& s) {
    if(!this->initialized) {
        return false;
    } else if(SDL_SetClipboardText(s.c_str()) < 0) {
        printf("failed to set clipboard text, err: %s\n", SDL_GetError());

        return false;
    }

    return true;
}

SDL_Scancode gfx::Renderer::convertKeyToSDLScancode(core::KEYBOARD_KEY gfxKey) {
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

void gfx::Renderer::swapBuffers() {
    if(!this->initialized) {
        return;
    }

    SDL_GL_SwapWindow(this->_pSdlWindow);
}
void gfx::Renderer::begin() {
    if(this->isDrawing) {
        return;
    }

    this->isDrawing = true;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void gfx::Renderer::end() {
    this->isDrawing = false;

	this->pollEvents();
	this->swapBuffers();
}

void gfx::Renderer::draw(const gfx::SpriteBatch& batch) {
    if(!this->isDrawing) {
        printf("DRAW CALLS ARE BETWEEN RENDERER.BEGIN() and RENDERER.END()\n");
        return;
    }

	if(this->spriteShaderProgram.id != this->boundShaderProgramID) {
		this->spriteShaderProgram.bindID();
	}
	glBindVertexArray(batch.vao);
	glDrawArrays(GL_TRIANGLES, 0, 6*batch.numSprites);
}
