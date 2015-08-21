#include "core/sdl2_mouse.hpp"

glm::vec2 mg::SDL2Mouse::getPosition() const {
	glm::vec2 v;

	if(SDL_WasInit(0) != 0) {
		SDL_PumpEvents();

		int x, y;

		SDL_GetMouseState(&x, &y);
		v.x = x;
		v.y = y;
	}

	return v;
}

bool mg::SDL2Mouse::isLeftButtonDown() const {
	if(SDL_WasInit(0) != 0) {
		SDL_PumpEvents();

		if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			return true;
		}
	}

	return false;
}
bool mg::SDL2Mouse::isMiddleButtonDown() const {
	if(SDL_WasInit(0) != 0) {
		SDL_PumpEvents();

		if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
			return true;
		}
	}

	return false;
}
bool mg::SDL2Mouse::isRightButtonDown() const {
	if(SDL_WasInit(0) != 0) {
		SDL_PumpEvents();

		if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			return true;
		}
	}

	return false;
}
