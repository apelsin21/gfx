#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <glm/glm.hpp>

namespace mg {
	class Mouse {
		public:
			virtual glm::vec2 getPosition() = 0;

			virtual bool isLeftButtonDown() = 0;
			virtual bool isMiddleButtonDown() = 0;
			virtual bool isRightButtonDown() = 0;
	};
}

#endif //MOUSE_HPP
