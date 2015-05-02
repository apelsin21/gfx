#include <stdio.h>
#include <tuple>
#include <exception>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/keyboard_keys.hpp"

#include "gfx/free_image_texture.hpp"
#include "gfx/free_type_font.hpp"
#include "gfx/renderer.hpp"
#include "gfx/shader.hpp"
#include "gfx/shader_program.hpp"
#include "gfx/default_shaders.hpp"
#include "gfx/shader_type.hpp"
#include "gfx/renderer_event.hpp"
#include "gfx/context_settings.hpp"
#include "gfx/sprite_batch.hpp"
#include "gfx/sprite.hpp"

int main() {
    gfx::FreeImageTexture tex;
    gfx::Renderer renderer;
    gfx::Shader vs, fs;
    gfx::ShaderProgram program;
    gfx::ContextSettings settings(3, 3, 24, true, true, true);
	gfx::SpriteBatch batch;
	gfx::Sprite* sprite;

    try {
        renderer.initialize("Test Window", glm::vec2(800, 600), settings);

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

		batch.initialize(program.getAttribLocation("v_pos"), program.getAttribLocation("v_uv"));

    } catch(const std::runtime_error& e) {
        printf("ERR: %s", e.what());
        return EXIT_FAILURE;
    }

	glm::vec2 pos;

    while(renderer.isOpen()) {
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            renderer.close();
        }
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_W)) {
			pos.y += 0.01f;
		}
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_S)) {
			pos.y -= 0.01f;
		}
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_A)) {
			pos.x -= 0.01f;
		}
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_D)) {
			pos.x += 0.01f;
		}

        renderer.begin();

		tex.bindID();
		program.bindID();

		batch.draw(tex, pos, 0.5f);
		batch.draw(tex, glm::vec2(0.5f, 0.5f), 0.2f);

		batch.drawAll();

        renderer.end();
    }

    vs.deleteID();
    fs.deleteID();
    program.deleteID();
    tex.deleteID();

    return EXIT_SUCCESS;
}
