#ifndef SDL2_KEYBOARD_HPP
#define SDL2_KEYBOARD_HPP

#include <string>

#include <SDL2/SDL.h>

#include "core/keyboard.hpp"
#include "core/keyboard_keys.hpp"

namespace mg {
	class SDL2Keyboard : public Keyboard {
		protected:
            const unsigned char* sdlKeyState;
			int sdlNumKeys;
		public:
			SDL2Keyboard();
			~SDL2Keyboard();

			bool isKeyDown(mg::KEY);
	};
}

#endif //SDL2_KEYBOARD_HPP
