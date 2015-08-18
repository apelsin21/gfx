#include "game/player.hpp"

mg::Player::Player() {
	this->pos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
}
mg::Player::~Player() {
}

void mg::Player::update(mg::SDL2Keyboard keyboard) {
	if(keyboard.isKeyDown(mg::KEY::W)) {
		this->pos.y += 0.1f;
	}
	if(keyboard.isKeyDown(mg::KEY::S)) {
		this->pos.y -= 0.1f;
	}
	if(keyboard.isKeyDown(mg::KEY::A)) {
		this->pos.x -= 0.1f;
	}
	if(keyboard.isKeyDown(mg::KEY::D)) {
		this->pos.x += 0.1f;
	}
}
