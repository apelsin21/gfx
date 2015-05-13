#include <stdio.h>
#include <stdlib.h>
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

		void render(gfx::SpriteBatch& batch, float dt) {
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
    gfx::GraphicsDevice graphicsDevice; //handles initialization of opengl and sdl2
    gfx::Shader vs, fs; //vertex, fragment shader
    gfx::ShaderProgram program;
    gfx::ContextSettings settings(3, 3, 24, true, true, false); //opengl 3.3, 24 depth bits, double buffered, vsync'd, core opengl profile
	gfx::SpriteBatch batch(10000);

	gfx::Font font;
    gfx::Texture tex;

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
        tex.loadFromFile("data/textures/test.png");

		font.createID();
		font.loadFromFile("data/fonts/FreeSans.ttf", 32);

		batch.initialize(program.getAttribLocation("v_pos"), program.getAttribLocation("v_uv")); //so the batch knows where to send things in the shader

    } catch(const std::runtime_error& e) {
        printf("ERR: %s", e.what());
        return EXIT_FAILURE;
    }

	graphicsDevice.setClearColor(gfx::CYAN); //"background" color

	program.bindID(); //use the program and the attached shaders
	font.bindID(); //use the texture. only one texture atlas is used, so no need to bind every frame

	std::vector<Ball> ballArray;

	//std::string text;
	//text.push_back((char)rand((float)' ', (float)'~'));
	//const float resetTime = 0.1666f * 15.0f;
	//float timer = resetTime;

	while(graphicsDevice.open) {
        if(graphicsDevice.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            graphicsDevice.open = false;
        }

		//if(timer >= 0.0f) {
		//	timer -= graphicsDevice.deltaTime;
		//} else {
		//	text.clear();
		//	text.push_back((char)rand((float)' ', (float)'~'));
		//	timer = resetTime;
		//}

        graphicsDevice.begin();

		printf("frametime: %f\n", graphicsDevice.deltaTime * 1000.0f);
		printf("fps: %u\n", graphicsDevice.fps);
		//printf("timer: %f, char: %c\n", timer, text[0]);
		
		batch.drawString(std::string("bajs korv"), font, glm::vec2(-1.0f, 0.0f), glm::vec2(0.1f, 0.1f));
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
