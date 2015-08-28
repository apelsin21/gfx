#include "game/player.hpp"

mg::Player::Player() {
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_horizontalAngle = glm::quarter_pi<float>();
	_verticalAngle = 0.f;
	_initialFoV = 60.f;
	_speed = 30.0f;
	_turningSpeed = 0.5f;
	_lastTime = static_cast<float>(std::clock()) / static_cast<float>(CLOCKS_PER_SEC);
}
mg::Player::~Player() {
}

void mg::Player::update(const mg::SDL2Keyboard& keyboard, mg::SDL2Mouse& mouse, const mg::SDL2Window& window) {
	_lastTime = _currentTime;
	_currentTime = static_cast<float>(std::clock()) / static_cast<float>(CLOCKS_PER_SEC);
	_deltaTime = _currentTime - _lastTime;

	glm::vec2 resolution = window.getResolution();
	glm::vec2 mousePosition = mouse.getPosition();
	mouse.setPosition(resolution / 2.0f, window);

	if(keyboard.isKeyDown(mg::KEY::UP)) {
		_verticalAngle += _turningSpeed * _deltaTime * 100.f;
	}
	if(keyboard.isKeyDown(mg::KEY::DOWN)) {
		_verticalAngle -= _turningSpeed * _deltaTime * 100.f;
	}
	if(keyboard.isKeyDown(mg::KEY::LEFT)) {
		_horizontalAngle += _turningSpeed * _deltaTime * 100.f;
	}
	if(keyboard.isKeyDown(mg::KEY::RIGHT)) {
		_horizontalAngle -= _turningSpeed * _deltaTime * 100.f;
	}

	_horizontalAngle += _turningSpeed * _deltaTime * (resolution.x/2.0f - mousePosition.x);
	_verticalAngle   += _turningSpeed * _deltaTime * (resolution.y/2.0f - mousePosition.y);

	_verticalAngle = glm::clamp(
			_verticalAngle,
			-glm::half_pi<float>(),
			glm::half_pi<float>()
	);

	if(_horizontalAngle < 0.f) {
		_horizontalAngle += glm::pi<float>() * 2.f;
	}
	if(_horizontalAngle > glm::pi<float>()) {
		_horizontalAngle -= glm::pi<float>() * 2.f;
	}

	glm::vec3 direction(
			glm::cos(_verticalAngle) * glm::sin(_horizontalAngle),
			glm::sin(_verticalAngle),
			glm::cos(_verticalAngle) * glm::cos(_horizontalAngle)
	);

	mouse.hide();

	glm::vec3 right(
			glm::sin(_horizontalAngle - glm::half_pi<float>()),
			0.0f,
			glm::cos(_horizontalAngle - glm::half_pi<float>())
	);

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

	_projectionMatrix = glm::perspective(
		glm::radians(_initialFoV),
		static_cast<float>(resolution.x) / static_cast<float>(resolution.y),
		0.01f,
		100.0f
	);
	_viewMatrix = glm::lookAt(
		_position,
		_position + direction,
		glm::cross(right, direction)
	);

}

glm::mat4 mg::Player::getModelMatrix() const {
	return _modelMatrix;
}
glm::mat4 mg::Player::getViewMatrix() const {
	return _viewMatrix;
}
glm::mat4 mg::Player::getProjectionMatrix() const {
	return _projectionMatrix;
}
