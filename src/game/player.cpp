#include "game/player.hpp"

mg::Player::Player() {
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_horizontalAngle = 3.1415f;
	_verticalAngle = 0.0f;
	_initialFoV = 60.0f;
	_speed = 3.0f;
	_mouseSpeed = 0.005f;
	_lastTime = static_cast<float>(std::clock()) / static_cast<float>(CLOCKS_PER_SEC);
}
mg::Player::~Player() {
}

glm::mat4 mg::Player::update(const mg::SDL2Keyboard& keyboard, const mg::SDL2Mouse& mouse) {
	_horizontalAngle += _mouseSpeed * (800.0f/2.0f - 400.0f);
	_verticalAngle += _mouseSpeed * (600.0f/2.0f - 300.0f);

	glm::vec3 direction(
			glm::cos(_verticalAngle) * glm::sin(_horizontalAngle),
			glm::sin(_verticalAngle),
			glm::cos(_verticalAngle) * glm::cos(_horizontalAngle)
	);

	glm::vec3 right(
			glm::sin(_horizontalAngle - 3.14f/2.0f),
			0,
			glm::cos(_horizontalAngle - 3.14f/2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);

	_lastTime = _currentTime;
	_currentTime = static_cast<float>(std::clock()) / static_cast<float>(CLOCKS_PER_SEC);
	_deltaTime = _currentTime - _lastTime;

	if(keyboard.isKeyDown(mg::KEY::W)) {
		_position += direction * _deltaTime * _speed;
	}
	if(keyboard.isKeyDown(mg::KEY::S)) {
		_position -= direction * _deltaTime * _speed;
	}
	if(keyboard.isKeyDown(mg::KEY::A)) {
		_position -= right * _deltaTime * _speed;
	}
	if(keyboard.isKeyDown(mg::KEY::D)) {
		_position += right * _deltaTime * _speed;
	}

	glm::mat4 projectionMatrix = glm::perspective(_initialFoV, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 viewMatrix = glm::lookAt(
		_position,
		_position + direction,
		up
	);

	return projectionMatrix * viewMatrix;
}
