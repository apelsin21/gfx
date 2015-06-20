#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <tuple>
#include <exception>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/keyboard_keys.hpp"

#include "gfx/texture.hpp"
#include "gfx/font.hpp"

#include "gfx/graphics_device.hpp"
#include "gfx/graphics_device_event.hpp"
#include "gfx/context_settings.hpp"

#include "gfx/shader.hpp"
#include "gfx/shader_program.hpp"
#include "gfx/shader_type.hpp"

#include "gfx/sprite_batch.hpp"

float rand(float LO, float HI) {
	return(LO + (float)rand() / ((float)RAND_MAX/(HI-LO)));
}

class Ball {
	protected:
	public:
		glm::vec2 pos, velocity;
		glm::vec4 uv;
		float scale, timer, speed, timerQuarter;

		Ball(const glm::vec2& p) {
			this->uv = glm::vec4(0.463f, 0.0f, 0.493f, 0.77f);
			this->pos = p;
			this->velocity = glm::vec2(rand(0.01f, 0.5f), rand(0.01f, 0.5f));

			this->timer = rand(1.0f, 3.0f);
			this->timerQuarter = this->timer/4.0f;
			this->scale = 0.05f;
		}
		~Ball() {
		}

		void resetTimer() {
			this->timer = 2.5f;
		}

		void updateTexCoords() {
			if(timer >= this->timerQuarter*3.5f) {
				uv = glm::vec4(0.0f, 0.5f, 0.5f, 1.0f);
			} else if(timer >= this->timerQuarter*2.5f) {
				uv = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f);
			} else if(timer >= this->timerQuarter * 1.5f) {
				uv = glm::vec4(0.0f, 0.0f, 0.5f, 0.5f);
			} else if(timer >= this->timerQuarter) {
				uv = glm::vec4(0.5f, 0.0f, 1.0f, 0.5f);
			} else if(timer >= 0.0f) {
				resetTimer();
			}
		}

		void render(mg::SpriteBatch& batch, float dt) {
			//this->timer -= dt;
			//this->updateTexCoords();
			
			if(this->pos.x >= 1.0f || this->pos.x <= -1.0f) {
				this->velocity.x *= -1;
			}
			if(this->pos.y >= 1.0f || this->pos.y <= -1.0f) {
				this->velocity.y *= -1;
			}

			this->pos += velocity * dt;
			batch.draw(this->pos, glm::vec2(this->scale, this->scale), this->uv);
		}
};

int main() {
    mg::GraphicsDevice graphicsDevice;
    mg::Shader vs, fs, main;
    mg::ShaderProgram program;
    mg::ContextSettings settings(3, 3, 24, true, true, false);
	mg::SpriteBatch batch(10000);

	mg::Font font;
    mg::Texture tex;

	std::srand(time(NULL));

    try {
        graphicsDevice.initialize("Test Window", glm::vec2(800, 600), settings);

        vs.createID(mg::SHADER_TYPE::SHADER_TYPE_VERTEX);
        fs.createID(mg::SHADER_TYPE::SHADER_TYPE_FRAGMENT);
        vs.loadFromFile("data/shaders/vertex.glsl");
        fs.loadFromFile("data/shaders/fragment.glsl");
		main.loadFromFile("src/main.cpp");
        vs.compile();
        fs.compile();

        program.createID();
        program.attachShader(vs);
        program.attachShader(fs);
        program.link();

        tex.createID();
        tex.loadFromFile("data/textures/test.png");

		font.createID();
		font.loadFromFile("data/fonts/FreeSans.ttf", 16);

		batch.initialize(program.getAttribLocation("v_pos"), program.getAttribLocation("v_uv"));

    } catch(const std::runtime_error& e) {
        printf("ERR: %s", e.what());
        return EXIT_FAILURE;
    }

	graphicsDevice.setClearColor(mg::CORN_FLOWER_BLUE);

	program.bindID();
	font.bindID();

	std::vector<Ball> ballArray;

	glm::vec2 pos(0.0f, 500.0f);
	float speed = 1000.0f;

	int timer;
	std::wstring fps(L"FPS: ");
	std::wstring frametime(L"Frametime: ");
	
	GLuint mat = glGetUniformLocation(program.id, "v_projection");

	std::wstring text;
	for(unsigned int i = 0; i < main.src.size(); i++) {
		text += main.src[i];
	}

	while(graphicsDevice.open) {
		if(graphicsDevice.isKeyPressed(mg::KEYBOARD_KEY::KEY_ESCAPE)) {
			graphicsDevice.open = false;
		}
		if(graphicsDevice.isKeyPressed(mg::KEYBOARD_KEY::KEY_W)) {
			pos.y += speed * graphicsDevice.deltaTime;
		}
		if(graphicsDevice.isKeyPressed(mg::KEYBOARD_KEY::KEY_S)) {
			pos.y -= speed * graphicsDevice.deltaTime;
		}
		if(graphicsDevice.isKeyPressed(mg::KEYBOARD_KEY::KEY_A)) {
			pos.x -= speed * graphicsDevice.deltaTime;
		}
		if(graphicsDevice.isKeyPressed(mg::KEYBOARD_KEY::KEY_D)) {
			pos.x += speed * graphicsDevice.deltaTime;
		}

		timer += graphicsDevice.fps;

		if(timer >= 60*60) {
			fps = L"FPS: ";
			fps += std::to_wstring(graphicsDevice.fps);

			frametime = L"Frametime: ";
			frametime += std::to_wstring(graphicsDevice.deltaTime * 1000.0f);

			timer = 0;
		}

		glUniformMatrix4fv(mat, 1, GL_FALSE, glm::value_ptr(glm::ortho(0.0f, (float)graphicsDevice.resolution.x, 0.0f, (float)graphicsDevice.resolution.y, -1.0f, 1.0f)));

        graphicsDevice.begin();
		batch.draw(font.cacheString, font, pos);
		//batch.draw(text, font, pos);
		batch.draw(fps, font, glm::vec2(0.f, 0.f));
		batch.draw(frametime, font, glm::vec2(0.f, 64.f));
		batch.drawAll();

        graphicsDevice.end();
    }

    vs.deleteID();
    fs.deleteID();
	font.deleteID();
    program.deleteID();
    tex.deleteID();

    return EXIT_SUCCESS;
}
