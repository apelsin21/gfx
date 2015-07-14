#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

#include "game/sprite.hpp"

namespace mg {
	class Level {
		protected:
		public:
			std::vector<mg::Sprite> sprites;

			Level();
			~Level();

			bool load(const std::string&);
	};
}

#endif //LEVEL_HPP
