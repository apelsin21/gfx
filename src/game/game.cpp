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
	
	//std::vector<float> vertexData = {
	//	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, //bottom left
	//	0.5f, 1.0f, 0.0f, 0.5f, 1.0f, //middle top
	//	1.0f, 0.0f, 0.0f, 1.0f, 0.0f,//bottom right
	//};

	//_buffer.allocate(vertexData.size(), true, mg::VertexFormat::PPPTT);
	//_buffer.update(vertexData);

	if(!_world.generate()) {
		printf("Failed to generate world.\n");
		return false;
	}

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

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


		GLint projLocation = _shader.getUniformLocation("v_projection");
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, &_player.update(_keyboard, _mouse)[0][0]);

		_texture.bindID();
		_renderer.render(_shader, _world.getBuffer());

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
