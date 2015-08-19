#include "game/game.hpp"

mg::Game::Game() {
	_window.setCaption("Platformer Game Thing");
	_window.setResolution(glm::vec2(800, 600));
}
mg::Game::~Game() {
}

bool mg::Game::load() {
    if(!_shader.loadFromFile("data/shaders/vertex.glsl", "data/shaders/fragment.glsl")) {
		printf("Shader failed to load!\n");
        return false;
    }

	if(!_texture.load("data/textures/terrain.png")) {
		printf("Texture %s failed to load!\n", _texture.path.c_str());
        return false;
    }
	
	if(!_font.load("data/fonts/FreeSans.ttf", 16)) {
		printf("Font %s failed to load!\n", _font.path);
		return false;
	}

    if(!_batch.initialize(_shader.getAttribLocation("v_pos"), _shader.getAttribLocation("v_uv"))) {
		printf("Batch failed to initialize!\n");
		return false;
	}

	//if(!_soundPlayer.initialize()) {
	//	printf("soundplayer failed to initialize.\n");
	//	return false;
	//}

	//if(!_sound.load("data/sounds/test2.opus")) {
	//	printf("failed to load sound.\n");
	//	return false;
	//}

	//if(!_soundPlayer.playSound(_sound)) {
	//	printf("failed to play sound.\n");
	//	return false;
	//}

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    _shader.bindID();

	return true;
}

void mg::Game::run() {
	bool run = true;

	while(run) {
		if(_keyboard.isKeyDown(mg::KEY::ESCAPE)) {
			run = false;
		}
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, _window.getResolution().x, _window.getResolution().y);

		GLint projLocation = _shader.getUniformLocation("projection");
		glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, &projection[0][0]);

		_batch.draw(L"-", this->_font, glm::vec2(32.0f, 0.5f), 0.01f);
		_batch.drawAll(_font.getID());

		for(unsigned int i = 0; i < _window.getNumEvents(); i++) {
			switch(_window.getEvent()) {
				default:
					break;
			}
		}

		_window.pollEvents();
		_window.swapBuffers();
	}
}
