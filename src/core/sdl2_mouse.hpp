#ifndef SDL2_MOUSE_HPP
#define SDL2_MOUSE_HPP

#include <SDL2/SDL.h>

#include "core/mouse.hpp"
#include "core/sdl2_window.hpp"

namespace mg {
	class SDL2Mouse : public Mouse {
		protected:
			bool hidden;
		public:
			glm::vec2 getPosition() const;

			//void setPosition(const glm::vec2&);
			void setPosition(const glm::vec2&, const mg::SDL2Window&);

			void hide();
			bool isHidden() const;

			bool isLeftButtonDown() const;
			bool isMiddleButtonDown() const;
			bool isRightButtonDown() const;
	};
}
#endif //SDL2_MOUSE_HPP
