#include "core/sdl2_window.hpp"

mg::SDL2Window::SDL2Window() {
	sdlWindow = nullptr;
	sdlContext = NULL;
	sdlWindowID = 0;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unable to initialize SDL2. Error: %s\n", SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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

std::string mg::SDL2Window::getCaption() const {
	std::string title;

	if(sdlWindow)
		title = SDL_GetWindowTitle(sdlWindow);

	return title;
}
void mg::SDL2Window::setCaption(const std::string& c) {
	if(sdlWindow)
		SDL_SetWindowTitle(sdlWindow, c.c_str());
}

glm::vec2 mg::SDL2Window::getResolution() const {
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

glm::vec2 mg::SDL2Window::getPosition() const {
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

bool mg::SDL2Window::isFullscreen() const {
	if(sdlWindow) {
		unsigned int flags = SDL_GetWindowFlags(sdlWindow);

		if(flags == SDL_WINDOW_FULLSCREEN || flags == SDL_WINDOW_FULLSCREEN_DESKTOP) {
			return true;
		}
	}

	return false;
}
bool mg::SDL2Window::isFocused() const {
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
bool mg::SDL2Window::isMaximized() const {
	if(sdlWindow) {
		unsigned int flags = SDL_GetWindowFlags(sdlWindow);

		if(flags == SDL_WINDOW_MAXIMIZED) {
			return true;
		}
	}

	return false;
}

unsigned int mg::SDL2Window::getNumEvents() const {
	return this->events.size();
}
mg::WINDOW_EVENT mg::SDL2Window::getEvent() {
	if(this->events.empty()) {
		return mg::WINDOW_EVENT::NOTHING;
	}

	mg::WINDOW_EVENT event = this->events[0];

	this->events.erase(this->events.begin());

	return event;
}
void mg::SDL2Window::pollEvents() {
	while(SDL_PollEvent(&this->sdlEvent)) {
		if(this->sdlEvent.type != SDL_WINDOWEVENT || this->sdlEvent.window.windowID != this->sdlWindowID) {
			break;
		}

		if(this->events.size() >= 512) {
			this->events.clear();
		}

		switch(this->sdlEvent.window.event) {
        case SDL_WINDOWEVENT_SHOWN:
			this->events.emplace_back(mg::WINDOW_EVENT::SHOWN);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
			this->events.emplace_back(mg::WINDOW_EVENT::HIDDEN);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
			this->events.emplace_back(mg::WINDOW_EVENT::EXPOSED);
            break;
        case SDL_WINDOWEVENT_MOVED:
			this->events.emplace_back(mg::WINDOW_EVENT::MOVED);
            break;
        case SDL_WINDOWEVENT_RESIZED:
			this->events.emplace_back(mg::WINDOW_EVENT::RESIZED);
			break;
        case SDL_WINDOWEVENT_MINIMIZED:
			this->events.emplace_back(mg::WINDOW_EVENT::MINIMIZED);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
			this->events.emplace_back(mg::WINDOW_EVENT::MAXIMIZED);
            break;
        case SDL_WINDOWEVENT_RESTORED:
			this->events.emplace_back(mg::WINDOW_EVENT::RESTORED);
            break;
        case SDL_WINDOWEVENT_ENTER:
			this->events.emplace_back(mg::WINDOW_EVENT::ENTERED);
            break;
        case SDL_WINDOWEVENT_LEAVE:
			this->events.emplace_back(mg::WINDOW_EVENT::LEFT);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
			this->events.emplace_back(mg::WINDOW_EVENT::FOCUS_GAINED);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
			this->events.emplace_back(mg::WINDOW_EVENT::FOCUS_LOST);
            break;
        case SDL_WINDOWEVENT_CLOSE:
			this->events.emplace_back(mg::WINDOW_EVENT::CLOSED);
            break;
		default:
			break;
		}
	}
}
void mg::SDL2Window::swapBuffers() {
	if(sdlWindow)
		SDL_GL_SwapWindow(sdlWindow);
}

SDL_Window* mg::SDL2Window::getSDLHandle() const {
	return sdlWindow;
}
