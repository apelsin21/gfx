#include "game/game.hpp"

mg::Game::Game() {
	window.setCaption("Platformer Game Thing");
	window.setResolution(glm::vec2(800, 600));
}
mg::Game::~Game() {
}

bool mg::Game::load() {
    if(!shader.loadFromFile("data/shaders/vertex.glsl", "data/shaders/fragment.glsl")) {
        return false;
    }

	if(!fiTexLoader.load("data/textures/terrain.png", texture)) {
        return false;
    }

    if(!batch.initialize(shader.getAttribLocation("v_pos"), shader.getAttribLocation("v_uv"))) {
		return false;
	}

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    shader.bindID();

	return true;
}

void mg::Game::run() {
	while(true) {
		if(keyboard.isKeyDown(mg::KEY::ESCAPE)) {
			break;
		}
	
		if(keyboard.isKeyDown(mg::KEY::W))
			pos.y += 0.1f;
		if(keyboard.isKeyDown(mg::KEY::S))
			pos.y -= 0.1f;
		if(keyboard.isKeyDown(mg::KEY::A))
			pos.x -= 0.1f;
		if(keyboard.isKeyDown(mg::KEY::D))
			pos.x += 0.1f;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, window.getResolution().x, window.getResolution().y);

        batch.draw(pos, glm::vec2(1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        batch.drawAll(texture.getID());

		window.swapBuffers();
	}
}
