#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <tuple>
#include <exception>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/keyboard_keys.hpp"

#include "gfx/free_image_texture.hpp"
#include "gfx/free_type_font.hpp"
#include "gfx/graphics_device.hpp"
#include "gfx/shader.hpp"
#include "gfx/shader_program.hpp"
#include "gfx/default_shaders.hpp"
#include "gfx/shader_type.hpp"
#include "gfx/graphics_device_event.hpp"
#include "gfx/context_settings.hpp"
#include "gfx/sprite_batch.hpp"
#include "gfx/sprite.hpp"

float rand(float LO, float HI) {
	return(LO + (float)rand() / ((float)RAND_MAX/(HI-LO)));
}

class Ball {
	protected:
	public:
		glm::vec2 pos;
		glm::vec4 uv;
		glm::vec2 velocity;
		float scale, timer;

		Ball() {
			this->uv = glm::vec4(0.5f, 0.5f, 1.0f, 0.0f);
			this->scale = 0.01f;
			this->velocity = glm::vec2(rand(-0.5f, 0.5f), rand(-0.5f, 0.5f));

			this->timer = 0.0f;
		}
		~Ball() {
		}

		bool timerIsBetween(float low, float high) {
			if(this->timer >= low && this->timer <= high) {
				return true;
			}
			return false;
		}
		void resetTimer() {
			this->timer = 0.0f;
		}

		void nextFrame() {
			if(this->timerIsBetween(0.0f, 0.5f)) {
				this->uv = glm::vec4(0.0f, 0.5f, 0.5f, 1.0f); //shows the first quarter of the texture
			} else if(this->timerIsBetween(0.5f, 1.0f)) {
				this->uv = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f); //shows the second quarter of the texture
			} else if(this->timerIsBetween(1.0f, 1.5f)) {
				this->uv = glm::vec4(0.0f, 0.0f, 0.5f, 0.5f); //shows the third quarter of the texture
			} else if(this->timerIsBetween(1.5f, 2.0f)) {
				this->uv = glm::vec4(0.5f, 0.0f, 1.0f, 0.5f); //shows the fourth quarter of the texture
			} else if(this->timer > 2.0f) {
				this->resetTimer();
			}

		}

		void render(gfx::SpriteBatch& batch, float dt) {
			this->timer += dt;

			this->nextFrame();

			if(this->pos.x >= 1.0f || this->pos.x <= -1.0f) {
				this->velocity.x *= -1;
			}
			if(this->pos.y >= 1.0f || this->pos.y <= -1.0f) {
				this->velocity.y *= -1;
			}

			this->pos += this->velocity * dt;
			batch.draw(this->pos, this->scale, this->uv);
		}
};

int main() {
    gfx::FreeImageTexture tex;
    gfx::GraphicsDevice graphicsDevice; //initializes opengl and sdl2
    gfx::Shader vs, fs;
    gfx::ShaderProgram program;
    gfx::ContextSettings settings(3, 3, 24, true, true, true); //opengl 3.3, 24 depth bits, double buffered, vsync'd, core opengl profile
	gfx::SpriteBatch batch(10000);
	gfx::Sprite* sprite;

	std::srand(time(NULL)); //seeds random number generator

    try {
        graphicsDevice.initialize("Test Window", glm::vec2(800, 600), settings); //title, resolution, context settings

        vs.createID(gfx::SHADER_TYPE::SHADER_TYPE_VERTEX);
        fs.createID(gfx::SHADER_TYPE::SHADER_TYPE_FRAGMENT);
        vs.loadFromFile("data/shaders/vertex.glsl");
        fs.loadFromFile("data/shaders/fragment.glsl");
        vs.compile();
        fs.compile();

        program.createID();
        program.attachShader(vs);
        program.attachShader(fs);
        program.link();

        tex.createID();
        tex.loadFromFile("test.png");

		batch.initialize(program.getAttribLocation("v_pos"), program.getAttribLocation("v_uv")); //so the batch knows where to send things in the shader

    } catch(const std::runtime_error& e) {
        printf("ERR: %s", e.what());
        return EXIT_FAILURE;
    }

	graphicsDevice.setClearColor(gfx::CYAN); //"background" color

	std::vector<Ball> ballArray;
	program.bindID(); //use the program and the attached shaders
	tex.bindID(); //use the texture. only one texture atlas is used, so no need to bind every frame
	while(graphicsDevice.open) {
        if(graphicsDevice.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            graphicsDevice.open = false;
        }
        if(graphicsDevice.isKeyPressed(core::KEYBOARD_KEY::KEY_A)) {
			if(ballArray.size() < batch.max) {
				ballArray.push_back(Ball());
			}
        }

        graphicsDevice.begin(); //clears the color buffer and the depth buffer, calculates deltatime and fps

		printf("frametime: %f\n", graphicsDevice.deltaTime * 1000.0f);
		printf("fps: %u\n", graphicsDevice.fps);
		printf("balls: %u\n", ballArray.size());

		for(unsigned int i = 0; i < ballArray.size(); i++) {
			ballArray[i].render(batch, graphicsDevice.deltaTime); //this doesn't actually draw anything, but updates the buffer in the SpriteBatch 
		}

		batch.drawAll(); //this draws every sprite

        graphicsDevice.end(); //swaps backbuffer with frontbuffer
    }

    vs.deleteID();
    fs.deleteID();
    program.deleteID();
    tex.deleteID();

    return EXIT_SUCCESS;
}
