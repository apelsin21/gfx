#include "game/player.hpp"

mg::Player::Player() {
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_horizontalAngle = 3.1415f;
	_verticalAngle = 0.0f;
	_initialFoV = 60.0f;
	_speed = 30.0f;
	_mouseSpeed = 0.5f;
	_lastTime = static_cast<float>(std::clock()) / static_cast<float>(CLOCKS_PER_SEC);
}
mg::Player::~Player() {
}

glm::mat4 mg::Player::update(const mg::SDL2Keyboard& keyboard, mg::SDL2Mouse& mouse, const mg::SDL2Window& window) {
	_lastTime = _currentTime;
	_currentTime = static_cast<float>(std::clock()) / static_cast<float>(CLOCKS_PER_SEC);
	_deltaTime = _currentTime - _lastTime;

	glm::vec2 resolution = window.getResolution();
	glm::vec2 mousePosition = mouse.getPosition();

	_horizontalAngle += _mouseSpeed * _deltaTime * (resolution.x/2.0f - mousePosition.x);
	_verticalAngle -= _mouseSpeed * _deltaTime * (resolution.y/2.0f - mousePosition.y);

	glm::vec3 direction(
			glm::cos(_verticalAngle) * glm::sin(_horizontalAngle),
			glm::sin(_verticalAngle),
			glm::cos(_verticalAngle) * glm::cos(_horizontalAngle)
	);

	mouse.hide();

	glm::vec3 right(
			glm::sin(_horizontalAngle - 3.1415f/2.0f),
			0.0f,
			glm::cos(_horizontalAngle - 3.1415f/2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);


	if(keyboard.isKeyDown(mg::KEY::W)) {
		_position += direction * _deltaTime * _speed;
	}
	if(keyboard.isKeyDown(mg::KEY::S)) {
		_position -= direction * _deltaTime * _speed;
	}
	if(keyboard.isKeyDown(mg::KEY::A)) {
		_position += right * _deltaTime * _speed;
	}
	if(keyboard.isKeyDown(mg::KEY::D)) {
		_position -= right * _deltaTime * _speed;
	}

	if(keyboard.isKeyDown(mg::KEY::Q)) {
		_speed -= 0.5f;

		if(_speed < 0.0f) {
			_speed = 0.0f;
		}
	}
	if(keyboard.isKeyDown(mg::KEY::E)) {
		_speed += 0.5f;

		if(_speed < 0.0f) {
			_speed = 0.0f;
		}
	}

	glm::mat4 projectionMatrix = glm::perspective(3.1415f * 1.5f, 4.0f / 3.0f, 0.001f, 100.0f);
	glm::mat4 viewMatrix = glm::lookAt(
		_position,
		_position + direction,
		up
	);

	mouse.setPosition(resolution / 2.0f, window);

	return projectionMatrix * viewMatrix;
}
