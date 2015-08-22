#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "core/sdl2_keyboard.hpp"
#include "core/sdl2_mouse.hpp"
#include "core/sdl2_window.hpp"

#include "game/entity.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

namespace mg {
	class Player : public mg::Entity {
		protected:
			float _horizontalAngle, _verticalAngle, _initialFoV, _speed, _mouseSpeed;

			float _deltaTime, _lastTime, _currentTime;
		public:
			Player();
			~Player();

			glm::mat4 update(const mg::SDL2Keyboard&, mg::SDL2Mouse&, const mg::SDL2Window&);
	};
}

#endif //PLAYER_HPP
