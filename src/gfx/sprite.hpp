#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <cstring>

#include "gfx/vertex.hpp"

namespace gfx {
    class Sprite {
		protected:
		public:
			float positions[12];
			float uvs[12];
			float colors[24];

			Sprite();
			~Sprite();
    };
}

#endif //SPRITE_HPP
