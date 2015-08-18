#include "game/game.hpp"

mg::Game::Game() {
	window.setCaption("Platformer Game Thing");
	window.setResolution(glm::vec2(800, 600));
}
mg::Game::~Game() {
}

bool mg::Game::load() {
    if(!shader.loadFromFile("data/shaders/vertex.glsl", "data/shaders/fragment.glsl")) {
		printf("Shader failed to load!\n");
        return false;
    }

	if(!texture.load("data/textures/terrain.png")) {
		printf("Texture %s failed to load!\n", texture.path.c_str());
        return false;
    }

    if(!batch.initialize(shader.getAttribLocation("v_pos"), shader.getAttribLocation("v_uv"))) {
		printf("Batch failed to initialize!\n");
		return false;
	}

	if(!sound_player.initialize()) {
		printf("soundplayer failed to initialize.\n");
		return false;
	}

	if(!sound.load("data/sounds/test2.opus")) {
		printf("failed to load sound.\n");
		return false;
	}

	if(!sound_player.playSound(sound)) {
		printf("failed to play sound.\n");
		return false;
	}

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    shader.bindID();

	return true;
}

void mg::Game::run() {
	bool run = true;

	while(run) {
		if(keyboard.isKeyDown(mg::KEY::ESCAPE)) {
			run = false;
		}
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, window.getResolution().x, window.getResolution().y);

		player.update(this->keyboard);
		this->sound_player.setPosition(player.getPosition());

		batch.draw(glm::vec2(player.getPosition().x, player.getPosition().y), glm::vec2(1.0f, 1.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		batch.drawAll(texture.getID());

		for(unsigned int i = 0; i < window.getNumEvents(); i++) {
			switch(window.getEvent()) {
				default:
					break;
			}
		}

		window.pollEvents();
		window.swapBuffers();
	}
}
