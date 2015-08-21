#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <glm/glm.hpp>

namespace mg {
	class Mouse {
		public:
			virtual glm::vec2 getPosition() const = 0;

			virtual bool isLeftButtonDown() const = 0;
			virtual bool isMiddleButtonDown() const = 0;
			virtual bool isRightButtonDown() const = 0;
	};
}

#endif //MOUSE_HPP
