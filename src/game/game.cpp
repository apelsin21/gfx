#include "game/game.hpp"

mg::Game::Game() {
	_window.setCaption("Game thing");
	_window.setResolution(glm::vec2(800, 600));
	_wireframe = false;
	_windowIsFocused = false;
	_lastKey = -1;
	_timesRendered = 0;
}
mg::Game::~Game() {
}

bool mg::Game::load() {
    if(!_shader.loadFromFile("data/shaders/vertex.glsl", "data/shaders/fragment.glsl")) {
		printf("Shader failed to load!\n");
        return false;
    }

	if(!_texture.load("data/textures/cave_rock.png", mg::TEXTURE_FILTER::NEAREST, mg::TEXTURE_WRAP::REPEAT)) {
		printf("Texture %s failed to load!\n", _texture.path.c_str());
        return false;
    }
	
	//if(!_font.load("data/fonts/FreeSans.ttf", 16)) {
	//	printf("Font %s failed to load!\n", _font.path.c_str());
	//	return false;
	//}

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
	
	_lastTime = std::clock();
	if(!_world.generateVoxels()) {
		printf("Failed to generate voxels.\n");
		return false;
	}
	_currentTime = std::clock();
	float voxelSeconds = (_currentTime - _lastTime) / static_cast<float>(CLOCKS_PER_SEC);
	printf("generateVoxels(): %f seconds\n", voxelSeconds);

	if(!_world.generateVertices()) {
		printf("Failed to generate vertices.\n");
		return false;
	}
	_currentTime = std::clock();
	float vertexSeconds = (_currentTime - _lastTime) / static_cast<float>(CLOCKS_PER_SEC);
	printf("generateVertices(): %f seconds\n", vertexSeconds);

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	return true;
}

void mg::Game::run() {
	bool run = true;

	while(run) {
		if(_keyboard.isKeyDown(mg::KEY::ESCAPE)) {
			_window.grabInput(false);
			_mouse.hide(false);
		}
		if(_keyboard.isKeyDown(mg::KEY::Q)) {
			run = false;
		}
		if(_keyboard.isKeyDown(mg::KEY::P)) {
			_wireframe = !_wireframe;

			if(_wireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			} else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
		if(_mouse.isLeftButtonDown()) {
			_window.grabInput(true);
			_mouse.hide(true);
			glm::vec2 res = glm::vec2(
				_window.getResolution().x / 2,
				_window.getResolution().y / 2
			);
			_mouse.setPosition(res, _window);
		}
		if(_keyboard.isKeyDown(mg::KEY::SPACE)) {
			if(!_world.setSphere(_player.getPosition(), 10, 10.f)) {
				printf("failed to add voxel\n");
			}
		}
		if(_keyboard.isKeyDown(mg::KEY::G)) {
			if(!_world.generateVertices()) {
				printf("world failed to generate vertices.\n");
			}
		}
		if(_keyboard.isKeyDown(mg::KEY::R)) {
			_world.reset();
			if(!_world.generateVoxels()) {
				printf("failed to re-generate voxels.\n");
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, _window.getResolution().x, _window.getResolution().y);

		if(_window.isInputGrabbed()) {
			_player.update(_keyboard, _mouse, _window);
		}

		GLint viewLocation = _shader.getUniformLocation("u_view");
		GLint projLocation = _shader.getUniformLocation("u_projection");
		GLint eyeLocation = _shader.getUniformLocation("u_eye_pos");

		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &_player.getViewMatrix()[0][0]);
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, &_player.getProjectionMatrix()[0][0]);
		glUniform3fv(eyeLocation, 1, &_player.getPosition()[0]);

		_texture.bindID();

		_currentTime = std::clock();
		float elapsedSeconds = (_currentTime - _lastTime) / static_cast<float>(CLOCKS_PER_SEC);
		//printf("elapsed: %f\n", elapsedSeconds);
		if(elapsedSeconds > 0.1f) {
			printf("times rendered per second: %u\n", _timesRendered);
			_timesRendered = 0;
			_lastTime = _currentTime;
		}

		_timesRendered++;
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
