#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "core/sdl2_keyboard.hpp"

#include "game/entity.hpp"

namespace mg {
	class Player : public mg::Entity {
		protected:
		public:
			Player();
			~Player();

			void update(mg::SDL2Keyboard);
	};
}

#endif //PLAYER_HPP
