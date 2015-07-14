#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <glm/glm.hpp>

namespace mg {
	class Sprite {
		public:
			glm::vec2 pos, scale;
			glm::vec4 uvs;
	};
}

#endif //SPRITE_HPP
