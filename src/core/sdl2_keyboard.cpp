#include "core/sdl2_keyboard.hpp"

mg::SDL2Keyboard::SDL2Keyboard() {
	sdlKeyState = nullptr;
	sdlNumKeys = 0;

	if(SDL_WasInit(0) != 0) {
		sdlKeyState = SDL_GetKeyboardState(&this->sdlNumKeys);
	}
}
mg::SDL2Keyboard::~SDL2Keyboard() {
}

bool mg::SDL2Keyboard::isKeyDown(const std::string& key) {
	if(SDL_WasInit(0) != 0) {
		SDL_PumpEvents();

		return sdlKeyState[SDL_GetScancodeFromName(key.c_str())] ? true : false;
	}

	return false;
}
