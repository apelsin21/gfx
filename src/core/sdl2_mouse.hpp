#ifndef SDL2_MOUSE_HPP
#define SDL2_MOUSE_HPP

#include <SDL2/SDL.h>

#include "core/mouse.hpp"

namespace mg {
	class SDL2Mouse : public Mouse {
		public:
			glm::vec2 getPosition();

			bool isLeftButtonDown();
			bool isMiddleButtonDown();
			bool isRightButtonDown();
	};
}
#endif //SDL2_MOUSE_HPP
