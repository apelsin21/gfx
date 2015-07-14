#include "core/sdl2_window.hpp"

mg::SDL2Window::SDL2Window() {
	sdlWindow = nullptr;
	sdlContext = NULL;
	sdlWindowID = 0;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unable to initialize SDL2. Error: %s\n", SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    sdlWindow = SDL_CreateWindow("MuggEngine Window",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			800, 600,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(!sdlWindow) {
        printf("Could not create SDL2 window. Error: %s\n", SDL_GetError());
    }

    sdlContext = SDL_GL_CreateContext(sdlWindow);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        printf("Failed to initialize GLEW. Error: %s\n", (char*)glewGetErrorString(err));
    }

    sdlWindowID = SDL_GetWindowID(sdlWindow);
}
mg::SDL2Window::~SDL2Window() {
    if(sdlContext) {
        SDL_GL_DeleteContext(sdlContext);
    }
    
    if(sdlWindow) {
        SDL_DestroyWindow(sdlWindow);
    }
    
	if(SDL_WasInit(0) != 0) {
    	SDL_Quit();
	}
}

std::string mg::SDL2Window::getCaption() {
	std::string title;

	if(sdlWindow)
		title = SDL_GetWindowTitle(sdlWindow);

	return title;
}
void mg::SDL2Window::setCaption(const std::string& c) {
	if(sdlWindow)
		SDL_SetWindowTitle(sdlWindow, c.c_str());
}

glm::vec2 mg::SDL2Window::getResolution() {
	glm::vec2 r;

	if(sdlWindow) {
		int x, y;

		SDL_GetWindowSize(sdlWindow, &x, &y);

		r.x = x;
		r.y = y;
	}

	return r;
}
void mg::SDL2Window::setResolution(const glm::vec2& r) {
	if(sdlWindow)
		SDL_SetWindowSize(sdlWindow, (int)r.x, (int)r.y);
}

glm::vec2 mg::SDL2Window::getPosition() {
	glm::vec2 v;

	if(sdlWindow) {
		int x, y;

		SDL_GetWindowPosition(sdlWindow, &x, &y);

		v.x = x;
		v.y = y;
	}

	return v;
}
void mg::SDL2Window::setPosition(const glm::vec2& p) {
	if(sdlWindow)
		SDL_SetWindowPosition(sdlWindow, (int)p.x, (int)p.y);
}

bool mg::SDL2Window::isFullscreen() {
	if(sdlWindow) {
		unsigned int flags = SDL_GetWindowFlags(sdlWindow);

		if(flags == SDL_WINDOW_FULLSCREEN || flags == SDL_WINDOW_FULLSCREEN_DESKTOP) {
			return true;
		}
	}

	return false;
}
bool mg::SDL2Window::isFocused() {
	if(sdlWindow) {
		unsigned int flags = SDL_GetWindowFlags(sdlWindow);

		if(flags == SDL_WINDOW_INPUT_FOCUS
		|| flags == SDL_WINDOW_MOUSE_FOCUS
		|| flags == SDL_WINDOW_INPUT_GRABBED) {
			return true;
		}
	}

	return false;
}
bool mg::SDL2Window::isMaximized() {
	if(sdlWindow) {
		unsigned int flags = SDL_GetWindowFlags(sdlWindow);

		if(flags == SDL_WINDOW_MAXIMIZED) {
			return true;
		}
	}

	return false;
}

void mg::SDL2Window::swapBuffers() {
	if(sdlWindow)
		SDL_GL_SwapWindow(sdlWindow);
}
