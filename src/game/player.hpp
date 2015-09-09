#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <chrono>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "core/sdl2_keyboard.hpp"
#include "core/sdl2_mouse.hpp"
#include "core/sdl2_window.hpp"

#include "game/entity.hpp"

namespace mg {
	class Player : public mg::Entity {
		protected:
			float _horizontalAngle, _verticalAngle, _initialFoV, _speed, _turningSpeed;

			float _deltaTime, _lastTime, _currentTime;

			glm::mat4 _modelMatrix, _viewMatrix, _projectionMatrix;
		public:
			Player();
			~Player();

			void update(const mg::SDL2Keyboard&, mg::SDL2Mouse&, const mg::SDL2Window&);

			glm::mat4 getModelMatrix() const;
			glm::mat4 getViewMatrix() const;
			glm::mat4 getProjectionMatrix() const;
	};
}

#endif //PLAYER_HPP
