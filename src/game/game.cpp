#include "game/game.hpp"

mg::Game::Game() {
	m_window.setCaption("Game thing");
	m_window.setResolution(glm::vec2(800, 600));
	m_wireframe = false;
	m_windowIsFocused = false;
	m_lastKey = -1;
	m_timesRendered = 0;

	m_fbo = std::make_shared<mg::FrameBuffer>();
	m_uniforms = std::make_shared<mg::ShaderUniforms>();

	m_worldBatch = std::make_shared<mg::Batch>();
	m_worldTexture = std::make_shared<mg::Texture>();
	m_worldShader = std::make_shared<mg::Shader>();

	m_screenBatch = std::make_shared<mg::Batch>();
	m_screenShader = std::make_shared<mg::Shader>();
	m_screenMesh = std::make_shared<mg::Mesh>();
}
mg::Game::~Game() {
}

bool mg::Game::load() {
    if(!m_worldShader->loadFromFile("data/shaders/world.vert", "data/shaders/world.frag")) {
        return false;
    }
	if(!m_textureLoader.load("data/textures/cave_rock.png", m_worldTexture)) {
        return false;
    }

	std::clock_t start = std::clock();
	if(!m_world.generateVoxels()) {
		return false;
	}
	std::clock_t end = std::clock();
 	double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	printf("world voxels took %f seconds.\n", elapsed_secs);

	start = std::clock();
	if(!m_world.generateMesh()) {
		return false;
	}
	end = std::clock();
 	elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	printf("world mesh took %f seconds.\n", elapsed_secs);

	if(!m_font.load("data/fonts/FreeSans.ttf", 32)) {
		fprintf(stderr, "failed to load font.\n");
		return false;
	}

	/*
	m_fontMesh = m_font.getMeshFromString(L"Bajskorv.");
	if(m_fontMesh == nullptr) {
		printf("failed to create mesh from font.\n");
		return false;
	}
	*/

	if(!m_screenShader->loadFromFile("data/shaders/screen.vert", "data/shaders/screen.frag")) {
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

	m_screenMesh->setVertexFormat(mg::VertexFormat::PPTT);
	if(!m_screenMesh->uploadVertexData(quad)) {
		return false;
	}

	if(!m_fbo->createColorTexture(glm::vec2(1680, 1050))) {
		printf("failed to create FBO color texture.\n");
		return false;
	}

	m_renderer.setClearColor(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));

	return true;
}

bool mg::Game::run() {
	bool run = true;

	while(run) {
		if(m_keyboard.isKeyDown(mg::KEY::ESCAPE)) {
			m_window.grabInput(false);
			m_mouse.hide(false);
		}
		if(m_keyboard.isKeyDown(mg::KEY::Q)) {
			run = false;
		}
		if(m_keyboard.isKeyDown(mg::KEY::P)) {
			m_wireframe = !m_wireframe;

			if(m_wireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			} else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}
		if(m_mouse.isLeftButtonDown()) {
			m_window.grabInput(true);
			m_mouse.hide(true);
			glm::vec2 res = glm::vec2(
				m_window.getResolution().x / 2,
				m_window.getResolution().y / 2
			);
			m_mouse.setPosition(res, m_window);
		}
		if(m_keyboard.isKeyDown(mg::KEY::SPACE)) {
			if(!m_world.setSphere(m_player.getPosition(), 10, -1.f)) {
				printf("failed to add voxel\n");
			}
		}
		if(m_keyboard.isKeyDown(mg::KEY::G)) {
			if(!m_world.generateMesh()) {
				printf("world failed to generate vertices.\n");
			}
		}
		if(m_keyboard.isKeyDown(mg::KEY::R)) {
			m_world.reset();
			if(!m_world.generateVoxels()) {
				printf("failed to re-generate voxels.\n");
			}
		}
		if(m_window.isInputGrabbed()) {
			m_player.update(m_keyboard, m_mouse, m_window);
		}

		m_uniforms->add("u_view", 		&m_player.getViewMatrix()[0][0]);
		m_uniforms->add("u_projection", 	&m_player.getProjectionMatrix()[0][0]);
		m_uniforms->add("u_eye_pos", 	std::make_shared<glm::vec3>(m_player.getPosition()));

		m_renderer.setSize(m_window.getResolution());

		if(!m_worldBatch->set(m_world.getMesh(), m_uniforms, m_worldTexture, m_worldShader)) {
			printf("failed to set worldBatch.\n");
			return false;
		}

		if(!m_renderer.render(m_fbo, m_worldBatch)) {
			printf("failed to render world.\n");
			return false;
		}

		if(!m_screenBatch->set(m_screenMesh, nullptr, m_fbo->getColorTexture(), m_screenShader)) {
			printf("failed to set screenBatch.\n");
			return false;
		}

		if(!m_renderer.render(m_screenBatch)) {
			printf("failed to render screen.\n");
			return false;
		}

		m_window.pollEvents();
		m_window.swapBuffers();
	}

	return true;
}
