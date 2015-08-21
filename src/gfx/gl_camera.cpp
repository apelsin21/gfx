#include "gfx/gl_camera.hpp"

mg::GLCamera::GLCamera() {
}
mg::GLCamera::~GLCamera() {
}

const glm::mat4& mg::GLCamera::getModelMatrix() const {
	return _model;
}
const glm::mat4& mg::GLCamera::getViewMatrix() const {
	return _view;
}
const glm::mat4& mg::GLCamera::getProjectionMatrix() const {
	return _projection;
}

void mg::GLCamera::setPosition(const glm::vec3& position) {
	_position = position;
}
void mg::GLCamera::setRotation(const glm::vec3& position) {
	_rotation = rotation;
}
void mg::GLCamera::setScale(const glm::vec3& position) {
	_scale = scale;
}

const glm::vec3& mg::GLCamera::getPosition() const {
	return _position;
}
const glm::vec3& mg::GLCamera::getRotation() const {
	return _rotation;
}
const glm::vec3& mg::GLCamera::getScale() const {
	return _scale;
}
