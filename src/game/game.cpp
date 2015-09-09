#include "game/game.hpp"

mg::Game::Game() {
	_window.setCaption("Game thing");
	_window.setResolution(glm::vec2(800, 600));
	_wireframe = false;
	_windowIsFocused = false;
	_lastKey = -1;
	_timesRendered = 0;

	_uniforms = std::make_shared<mg::ShaderUniforms>();
	_worldBatch = std::make_shared<mg::Batch>();
	_worldTexture = std::make_shared<mg::Texture>();
	_worldShader = std::make_shared<mg::Shader>();

	_screenBatch = std::make_shared<mg::Batch>();
	_screenShader = std::make_shared<mg::Shader>();
	_screenMesh = std::make_shared<mg::Mesh>();
}
mg::Game::~Game() {
}

bool mg::Game::load() {
    if(!_worldShader->loadFromFile("data/shaders/world.vert", "data/shaders/world.frag")) {
        return false;
    }
	if(!_textureLoader.load("data/textures/cave_rock.png", _worldTexture)) {
        return false;
    }

	if(!_world.generateVoxels()) {
		return false;
	}
	if(!_world.generateMesh()) {
		return false;
	}

	if(!_screenShader->loadFromFile("data/shaders/screen.vert", "data/shaders/screen.frag")) {
		return false;
	}

	std::vector<float> quad = {
    	-1.0f,  1.0f,  0.0f, 1.0f,
    	 1.0f,  1.0f,  1.0f, 1.0f,
    	 1.0f, -1.0f,  1.0f, 0.0f,

    	 1.0f, -1.0f,  1.0f, 0.0f,
    	-1.0f, -1.0f,  0.0f, 0.0f,
    	-1.0f,  1.0f,  0.0f, 1.0f
	};

	_screenMesh->setVertexFormat(mg::VertexFormat::PPTT);
	if(!_screenMesh->uploadVertexData(quad)) {
		return false;
	}

	if(!_fbo.createColorTexture(glm::vec2(800, 600))) {
		printf("failed to create FBO color texture.\n");
		return false;
	}

	_renderer.setClearColor(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	return true;
}

bool mg::Game::run() {
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
			if(!_world.generateMesh()) {
				printf("world failed to generate vertices.\n");
			}
		}
		if(_keyboard.isKeyDown(mg::KEY::R)) {
			_world.reset();
			if(!_world.generateVoxels()) {
				printf("failed to re-generate voxels.\n");
			}
		}
		if(_window.isInputGrabbed()) {
			_player.update(_keyboard, _mouse, _window);
		}

		_uniforms->add("u_view", 		&_player.getViewMatrix()[0][0]);
		_uniforms->add("u_projection", 	&_player.getProjectionMatrix()[0][0]);
		_uniforms->add("u_eye_pos", 	std::make_shared<glm::vec3>(_player.getPosition()));

		if(!_worldBatch->set(_world.getMesh(), _uniforms, _worldTexture, _worldShader)) {
			printf("failed to set worldBatch.\n");
			return false;
		}

		_renderer.setSize(_window.getResolution());
		if(!_renderer.render(_fbo, _worldBatch)) {
			printf("failed to render world.\n");
			return false;
		}

		if(!_screenBatch->set(_screenMesh, nullptr, _fbo.getColorTexture(), _screenShader)) {
			printf("failed to set screenBatch.\n");
			return false;
		}

		if(!_renderer.render(_screenBatch)) {
			printf("failed to render screen.\n");
			return false;
		}

		_window.pollEvents();
		_window.swapBuffers();
	}

	return true;
}
