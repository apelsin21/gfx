#include <stdio.h>
#include <tuple>
#include <exception>

#define GLEW_STATIC
#include <GL/glew.h>

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
#include "gfx/sprite_manager.hpp"
#include "gfx/sprite.hpp"

int main() {
    gfx::FreeTypeFont font;
    gfx::FreeImageTexture tex;
    gfx::Renderer renderer;
    gfx::Shader vs, fs;
    gfx::ShaderProgram program;
    gfx::ContextSettings settings(3, 0, 24, false, true, true);
	gfx::SpriteManager spriteManager;

    try {
        renderer.initialize("Test Window", glm::vec2(800, 600), settings);

        vs.createID(gfx::SHADER_TYPE::SHADER_TYPE_VERTEX);
        fs.createID(gfx::SHADER_TYPE::SHADER_TYPE_FRAGMENT);
        vs.loadFromMemory(gfx::defaultSpriteVertexShader);
        fs.loadFromMemory(gfx::defaultSpriteFragmentShader);
        vs.compile();
        fs.compile();

        program.createID();
        program.attachShader(vs);
        program.attachShader(fs);
        program.link();

        tex.createID();
        tex.loadFromFile("test.png");

		renderer.spriteShaderProgram = program;

		spriteManager.initialize(program.getAttribLocation("v_pos"), 
				program.getAttribLocation("v_uv"),
			   	program.getAttribLocation("v_color"));

    } catch(const std::runtime_error& e) {
        printf("ERR: %s", e.what());
        return EXIT_FAILURE;
    }

    renderer.setClearColor(gfx::Color(0.0f, 1.0f, 1.0f, 1.0f));

	spriteManager.addSprite();

    while(renderer.isOpen()) {
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            renderer.close();
            break;
        }
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_F11)) {
            renderer.setFullscreen();
        } else if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_F12)) {
            renderer.setWindowed();
        }

        renderer.begin();
        tex.bindID();
		renderer.drawSpriteManager(spriteManager);
        renderer.end();

        renderer.pollEvents();
        renderer.swapBuffers();
    }

    vs.deleteID();
    fs.deleteID();
    program.deleteID();
    tex.deleteID();

    return EXIT_SUCCESS;
}
