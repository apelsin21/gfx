#include "gfx/graphics_device.hpp"

mg::GraphicsDevice::GraphicsDevice() {
    this->clearColor = Color(0.0f, 0.0f, 0.0f, 1.0f);
    this->resolution = glm::vec2(800, 600);

    this->isDrawing = false;
    this->open = false;
    this->fullscreen = false;
    this->initialized = false;
    this->maximized = false;
    this->hidden = false;
    this->focused = false;

	this->boundTextureID = 0;
	this->boundShaderProgramID = 0;
	this->fps = 0;
	this->deltaTime = 0.0f;
	this->currentFrameTime = 0.0f;
	this->lastFrameTime = 0.0f;

    this->_sdlWindowID = 0;
    this->_sdlContext = NULL;
    this->_pSdlWindow = nullptr;
}
mg::GraphicsDevice::~GraphicsDevice() {
}

bool mg::GraphicsDevice::initialize(const std::string& t, const glm::vec2& res) {
    if(this->initialized) {
        throw std::runtime_error("renderer is already initialized!\n");
        return false;
    }
}

void mg::GraphicsDevice::setClearColor(const mg::Color& c) {
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
mg::Color mg::GraphicsDevice::getClearColor() {
    return this->clearColor;
}

std::string mg::GraphicsDevice::getTitle() {
    return this->title;
}
bool mg::GraphicsDevice::setTitle(const std::string& t) {
    if(this->initialized) {
    	this->title = t;
        SDL_SetWindowTitle(this->_pSdlWindow, this->title.c_str());
        return true;
    }

    return false;
}

glm::i32vec2 mg::GraphicsDevice::getResolution() {
    return this->resolution;
}
bool mg::GraphicsDevice::setResolution(const glm::i32vec2& r) {
    if(this->initialized) {
		this->resolution = r;
        SDL_SetWindowSize(this->_pSdlWindow, this->resolution.x, this->resolution.y);
        return true;
    }

    return false;
}

glm::i32vec2 mg::GraphicsDevice::getPosition() {
    return this->position;
}
bool mg::GraphicsDevice::setPosition(const glm::i32vec2& p) {
    if(this->initialized) {
		this->position = p;
        SDL_SetWindowPosition(this->_pSdlWindow, p.x, p.y);
        return true;
    }

    return false;
}

bool mg::GraphicsDevice::isOpen() {
    return this->open;
}
void mg::GraphicsDevice::close() {
    this->open = false;
}

bool mg::GraphicsDevice::isFullscreen() {
    return this->fullscreen;
}
void mg::GraphicsDevice::setFullscreen() {
    if(!this->initialized) {
        throw std::runtime_error("tried to set uninitialized renderer to fullscreen.\n");
    }

    if(SDL_SetWindowFullscreen(this->_pSdlWindow, SDL_WINDOW_FULLSCREEN) < 0) {
        throw std::runtime_error("failed to set renderer to fullscreen.\n");
    } else {
        this->fullscreen = true;
    }
}
void mg::GraphicsDevice::setBorderlessFullscreen() {
    if(!this->initialized) {
        throw std::runtime_error("tried to set uninitialized renderer to borderless fullscreen!\n");
    }

    if(SDL_SetWindowFullscreen(this->_pSdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0) {
        throw std::runtime_error("failed to set renderer to borderless fullscreen!\n");
    } else {
        this->fullscreen = true;
    }
}
void mg::GraphicsDevice::setWindowed() {
    if(!this->initialized) {
        throw std::runtime_error("tried to set uninitialized renderer to windowed mode.\n");
    }    

    if(SDL_SetWindowFullscreen(this->_pSdlWindow, 0) < 0) {
        throw std::runtime_error("failed to set renderer to windowed mode.\n");
    } else {
        this->fullscreen = false;
    }
}

bool mg::GraphicsDevice::isMaximized() {
    return this->maximized;
}
bool mg::GraphicsDevice::setMaximized(bool m) {
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

bool mg::GraphicsDevice::isHidden() {
    return this->hidden;
}
bool mg::GraphicsDevice::setHidden(bool h) {
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

bool mg::GraphicsDevice::isFocused() {
	return this->focused;
}
bool mg::GraphicsDevice::setFocused(bool f) {
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

bool mg::GraphicsDevice::hasPressedKey() {
	for(unsigned int i = 0; i < (int)SDL_Scancode::SDL_NUM_SCANCODES; i++) {
		if(this->_pSdlKeyboardState[i] != 0) {
			return true;
		}
	}

	return false;
}
std::vector<mg::KEYBOARD_KEY> mg::GraphicsDevice::getPressedKeys() {
	std::vector<mg::KEYBOARD_KEY> pressedKeys;

	for(unsigned int i = 0; i < (int)SDL_Scancode::SDL_NUM_SCANCODES; i++) {
		if(this->_pSdlKeyboardState[i] != 0) {
			pressedKeys.emplace_back((mg::KEYBOARD_KEY)i);
		}
	}

	return pressedKeys;
}
bool mg::GraphicsDevice::isKeyPressed(mg::KEYBOARD_KEY key) {
    return this->_pSdlKeyboardState[convertKeyToSDLScancode(key)];
}

void mg::GraphicsDevice::pollEvents() {
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

std::string mg::GraphicsDevice::getClipboardString() {
    std::string returnval;

    if(this->initialized && SDL_HasClipboardText() == SDL_TRUE) {
        //Because this needs to be manually freed
        char* temp_clip = SDL_GetClipboardText();

        returnval = temp_clip;

        free(temp_clip);
    }

    return returnval;
}
bool mg::GraphicsDevice::setClipboardString(const std::string& s) {
    if(!this->initialized) {
        return false;
    } else if(SDL_SetClipboardText(s.c_str()) < 0) {
        printf("failed to set clipboard text, err: %s\n", SDL_GetError());

        return false;
    }

    return true;
}

void mg::GraphicsDevice::swapBuffers() {
    if(!this->initialized) {
        return;
    }

    SDL_GL_SwapWindow(this->_pSdlWindow);
}
void mg::GraphicsDevice::begin() {
    if(this->isDrawing) {
        return;
    }

    this->isDrawing = true;

	this->lastFrameTime = this->currentFrameTime;
	this->currentFrameTime = SDL_GetTicks();
	this->deltaTime = (this->currentFrameTime - this->lastFrameTime) / 1000.0f;
	this->fps = 1/this->deltaTime;

    glClear(GL_COLOR_BUFFER_BIT);
}
void mg::GraphicsDevice::end() {
    this->isDrawing = false;

	this->pollEvents();
	this->swapBuffers();
}
