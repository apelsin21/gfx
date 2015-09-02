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
	//delete _gwenBar;
	//delete _gwenLabel;
	//delete _gwenCanvas;
	//delete _gwenSkin;
	//delete _gwenRenderer;
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
	//	printf("failed to load font.\n");
	//	return false;
	//}

	if(!_world.generateVoxels()) {
		printf("Failed to generate voxels.\n");
		return false;
	}
	if(!_world.generateVertices()) {
		printf("Failed to generate vertices.\n");
		return false;
	}

	_mesh.setVertexFormat(mg::VertexFormat::PPPNNN);
	if(!mesh.setData(_world.getVertices())) {
		printf("failed to set mesh data.\n");
		return false;
	}

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
		if(_window.isInputGrabbed()) {
			_player.update(_keyboard, _mouse, _window);
		}

		// these can be set on a frame by frame basis
		_uniforms.set("u_view", 		&_player.getViewMatrix()[0][0]);
		_uniforms.set("u_projection", 	&_player.getProjectionMatrix()[0][0]);
		_uniforms.set("u_eye_pos", 		&_player.getPosition()[0][0]);

		// a batch is a draw commmand that contains
		// all information needed for it to be rendered.
		// the shader, the vertices, the uniforms, the texture
		// it uses.
		//
		// it is not necessary to update the batch every frame,
		// but since the uniforms are updated that often,
		// the batch will need to be, too.
		//
		// it will automatically detect any changed parameter
		// and only change necessary state.
		_batch.set(_mesh, _uniforms, _shader, _texture);

		_renderer.setClearColor(mg::Color::Black);
		_renderer.setSize(_window.getResolution());
		// this could later be changed to renderer.queue(batch)
		// and require a later renderer.render(mg::FrameBuffer)
		// for added efficiency
		_renderer.render(_batch);

		_window.pollEvents();
		_window.swapBuffers();
	}
}
