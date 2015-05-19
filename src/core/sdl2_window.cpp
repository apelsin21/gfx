#include "core/sdl2_window.hpp"

mg::SDL2Window::SDL2Window() : Window() {
	this->_pSdlWindow = nullptr;
	this->_sdlContext = 0;
	this->_sdlWindowID = 0;
}
mg::SDL2Window::~SDL2Window() {
    if(this->_sdlContext) {
        SDL_GL_DeleteContext(this->_sdlContext);
    }
    
    if(this->_pSdlWindow) {
        SDL_DestroyWindow(this->_pSdlWindow);
    }
    
    SDL_Quit();
}
bool mg::SDL2Window::init(const std::string& t, int w, int h, const mg::ContextSettings& settings) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::string errMsg("Unable to initialize SDL\n");
        errMsg += SDL_GetError();
        errMsg += "\n";
        throw std::runtime_error(errMsg);
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settings.major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settings.minor);

    if(settings.doubleBuffered) {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    } else {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
    }

    if(settings.coreProfile) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);                                                                                                          
	}

	if(settings.vsync) {
		SDL_GL_SetSwapInterval(1);
	} else {
		SDL_GL_SetSwapInterval(0);
	}

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, settings.depthBits);

    this->_pSdlWindow = SDL_CreateWindow(title.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            w, h,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(!this->_pSdlWindow) {
        std::string errMsg("Could not create SDL2 window, error:\n");
        errMsg += SDL_GetError();
        errMsg += "\n";
        throw std::runtime_error(errMsg);
        return false;
    }

    this->_sdlContext = SDL_GL_CreateContext(this->_pSdlWindow);

	this->open = true;
	this->hidden = false;

	return true;
}

std::string mg::SDL2Window::getTitle() {
    return this->title;
}
bool mg::SDL2Window::setTitle(const std::string& t) {
    if(this->initialized) {
    	this->title = t;
        SDL_SetWindowTitle(this->_pSdlWindow, this->title.c_str());
        return true;
    }

    return false;
}

int mg::SDL2Window::getWidth() {
	return this->width;
}
int mg::SDL2Window::getHeight() {
	return this->height;
}
void mg::SDL2Window::setResolution(int w, int h) {
    if(this->initialized) {
        SDL_SetWindowSize(this->_pSdlWindow, w, h);
		this->width = w;
		this->height = h;
    }
}

int mg::SDL2Window::getPositionX() {
    return this->x;
}
int mg::SDL2Window::getPositionY() {
    return this->y;
}
void mg::SDL2Window::setPosition(int _x, int _y) {
    if(this->initialized) {
        SDL_SetWindowPosition(this->_pSdlWindow, _x, _y);
		this->x = _x;
		this->y = _y;
    }
}

bool mg::SDL2Window::isOpen() {
    return this->open;
}
void mg::SDL2Window::close() {
    this->open = false;
}

bool mg::SDL2Window::isFullscreen() {
    return this->fullscreen;
}
void mg::SDL2Window::setFullscreen() {
    if(!this->initialized) {
        throw std::runtime_error("tried to set uninitialized renderer to fullscreen.\n");
    }

    if(SDL_SetWindowFullscreen(this->_pSdlWindow, SDL_WINDOW_FULLSCREEN) < 0) {
        throw std::runtime_error("failed to set renderer to fullscreen.\n");
    } else {
        this->fullscreen = true;
    }
}
void mg::SDL2Window::setBorderlessFullscreen() {
    if(!this->initialized) {
        throw std::runtime_error("tried to set uninitialized renderer to borderless fullscreen!\n");
    }

    if(SDL_SetWindowFullscreen(this->_pSdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0) {
        throw std::runtime_error("failed to set renderer to borderless fullscreen!\n");
    } else {
        this->fullscreen = true;
    }
}
void mg::SDL2Window::setWindowed() {
    if(!this->initialized) {
        throw std::runtime_error("tried to set uninitialized renderer to windowed mode.\n");
    }    

    if(SDL_SetWindowFullscreen(this->_pSdlWindow, 0) < 0) {
        throw std::runtime_error("failed to set renderer to windowed mode.\n");
    } else {
        this->fullscreen = false;
    }
}

bool mg::SDL2Window::isMaximized() {
    return this->maximized;
}
bool mg::SDL2Window::setMaximized(bool m) {
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

bool mg::SDL2Window::isHidden() {
    return this->hidden;
}
bool mg::SDL2Window::setHidden(bool h) {
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

bool mg::SDL2Window::isFocused() {
	return this->focused;
}
bool mg::SDL2Window::setFocused(bool f) {
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

std::string mg::SDL2Window::getClipboardString() {
    std::string returnval;

    if(this->initialized && SDL_HasClipboardText() == SDL_TRUE) {
        //Because this needs to be manually freed
        char* temp_clip = SDL_GetClipboardText();

        returnval = temp_clip;

        free(temp_clip);
    }

    return returnval;
}
bool mg::SDL2Window::setClipboardString(const std::string& s) {
    if(!this->initialized) {
        return false;
    } else if(SDL_SetClipboardText(s.c_str()) < 0) {
        printf("failed to set clipboard text, err: %s\n", SDL_GetError());

        return false;
    }

    return true;
}

void mg::SDL2Window::swapBuffers() {
    if(!this->initialized) {
        return;
    }

    SDL_GL_SwapWindow(this->_pSdlWindow);
}
