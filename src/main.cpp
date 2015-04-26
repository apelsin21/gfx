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

int main() {
    gfx::FreeTypeFont font;
    gfx::FreeImageTexture tex;

    gfx::Renderer renderer;
    gfx::Shader vs, fs;
    gfx::ShaderProgram program;

    try {
        renderer.initialize("Window", 3, 0, false);

        vs.createID(gfx::SHADER_TYPE::SHADER_TYPE_VERTEX);
        fs.createID(gfx::SHADER_TYPE::SHADER_TYPE_FRAGMENT);

        vs.loadFromMemory(gfx::defaultFontVertexShader);
        fs.loadFromMemory(gfx::defaultFontFragmentShader);

        vs.compile();
        fs.compile();

        program.createID();

        program.attachShader(vs);
        program.attachShader(fs);

        program.link();

        tex.createID();
        tex.loadFromFile("data/textures/sprite.png");

		renderer.fontShaderProgram = program;
    } catch(const std::runtime_error& e) {
        printf("ERR: %s", e.what());
        return EXIT_FAILURE;
    }

    while(renderer.isOpen()) {
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
             renderer.close();
        }

        renderer.begin();
        renderer.drawTexture(tex, glm::vec2(400, 300));
        renderer.drawText(font, "bajs", glm::vec2(0, 0));
        renderer.end();

        renderer.pollEvents();
        renderer.swapBuffers();
    }

    tex.deleteID();
    vs.deleteID();
    fs.deleteID();
    program.deleteID();

    return EXIT_SUCCESS;
}
