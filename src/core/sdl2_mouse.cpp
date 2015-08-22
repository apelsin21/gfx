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

//void mg::SDL2Mouse::setPosition(const glm::vec2& position) {
//	if(SDL_WarpMouseGlobal((int)position.x, (int)position.y) < 0) {
//		printf("Failed to set SDL2Mouse position to %ix%i.\n", (int)position.x, (int)position.y);
//	}
//}
void mg::SDL2Mouse::setPosition(const glm::vec2& position, const mg::SDL2Window& window) {
	if(window.getSDLHandle() == nullptr) {
		printf("Failed to set SDL2Mouse position to %ix%i.\n", (int)position.x, (int)position.y);
		return;
	}

	SDL_WarpMouseInWindow(window.getSDLHandle(), (int)position.x, (int)position.y);
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

void mg::SDL2Mouse::hide() {
	if(SDL_ShowCursor(SDL_DISABLE) < 0 ) {
		printf("Failed to hide cursor.\n");
	}
}
bool mg::SDL2Mouse::isHidden() const {
	return SDL_ShowCursor(-1) ? true : false;
}
