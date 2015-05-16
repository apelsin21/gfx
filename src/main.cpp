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
				uv = glm::vec4(0.0f, 0.5f, 0.5f, 1.0f); //shows the first quarter of the texture
			} else if(timer >= this->timerQuarter*2.5f) {
				uv = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f); //shows the second quarter of the texture
			} else if(timer >= this->timerQuarter * 1.5f) {
				uv = glm::vec4(0.0f, 0.0f, 0.5f, 0.5f); //shows the third quarter of the texture
			} else if(timer >= this->timerQuarter) {
				uv = glm::vec4(0.5f, 0.0f, 1.0f, 0.5f); //shows the fourth quarter of the texture
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
    mg::GraphicsDevice graphicsDevice; //handles initialization of opengl and sdl2
    mg::Shader vs, fs; //vertex, fragment shader
    mg::ShaderProgram program;
    mg::ContextSettings settings(3, 3, 24, true, true, false); //opengl 3.3, 24 depth bits, double buffered, vsync'd, core opengl profile
	mg::SpriteBatch batch(10000);

	mg::Font font;
    mg::Texture tex;

	std::srand(time(NULL)); //seeds random number generator

    try {
        graphicsDevice.initialize("Test Window", glm::vec2(800, 600), settings); //title, resolution, context settings

        vs.createID(mg::SHADER_TYPE::SHADER_TYPE_VERTEX);
        fs.createID(mg::SHADER_TYPE::SHADER_TYPE_FRAGMENT);
        vs.loadFromFile("data/shaders/vertex.glsl");
        fs.loadFromFile("data/shaders/fragment.glsl");
        vs.compile();
        fs.compile();

        program.createID();
        program.attachShader(vs);
        program.attachShader(fs);
        program.link();

        tex.createID();
        tex.loadFromFile("data/textures/test.png");

		font.createID();
		font.loadFromFile("data/fonts/FreeSans.ttf", 32);

		batch.initialize(program.getAttribLocation("v_pos"), program.getAttribLocation("v_uv")); //so the batch knows where to send things in the shader

    } catch(const std::runtime_error& e) {
        printf("ERR: %s", e.what());
        return EXIT_FAILURE;
    }

	graphicsDevice.setClearColor(mg::CORN_FLOWER_BLUE); //"background" color

	program.bindID(); //use the program and the attached shaders
	font.bindID(); //use the texture. only one texture atlas is used, so no need to bind every frame

	std::vector<Ball> ballArray;

	glm::vec2 pos(0.0f, 500.0f);
	float speed = 1000.0f;

	int timer;
	std::wstring stats;
	
	GLuint mat = glGetUniformLocation(program.id, "v_projection");

	mg::Shader tempThing;
	tempThing.loadFromFile("src/main.cpp");

	std::wstring text;
	for(unsigned int i = 0; i < tempThing.src.size(); i++) {
		text += tempThing.src[i];
	}

	while(graphicsDevice.open) {
		if(graphicsDevice.isKeyPressed(mg::KEYBOARD_KEY::KEY_ESCAPE)) {
			graphicsDevice.open = false;
		}

		timer += graphicsDevice.fps;

		if(timer >= 60*60) {
			stats = L"FPS: ";
			stats += std::to_wstring(graphicsDevice.fps);

			timer = 0;
		}

		glUniformMatrix4fv(mat, 1, GL_FALSE, glm::value_ptr(glm::ortho(0.0f, (float)graphicsDevice.resolution.x, 0.0f, (float)graphicsDevice.resolution.y, -1.0f, 1.0f)));

        graphicsDevice.begin();
		batch.draw(L"abcdefghijklmnopqrstuvwxyzåäö\nABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ\n1234567890!#¤%&/\"()=?`^*_-.,:;½§", font, pos);
		//batch.draw(text, font, glm::vec2(0.0f, graphicsDevice.resolution.y - 32.0f));
		batch.draw(stats, font, glm::vec2(0.f, 0.f));
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
