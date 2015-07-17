#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

#include "game/sprite.hpp"

#include "gfx/sprite_batch.hpp"
#include "gfx/gl_texture.hpp"

namespace mg {
	class Level {
		protected:
		public:
			std::vector<mg::Sprite> sprites;

			Level();
			~Level();

			bool load(const std::string&);

			void render(mg::SpriteBatch&);
	};
}

#endif //LEVEL_HPP
