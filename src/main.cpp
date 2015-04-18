#include <stdio.h>
#include <tuple>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/sdl2_window.hpp"
#include "core/window_event.hpp"
#include "core/keyboard_keys.hpp"

#include "gfx/free_image_texture.hpp"
#include "gfx/free_type_font.hpp"
#include "gfx/gl_renderer.hpp"
#include "gfx/gl_shader.hpp"
#include "gfx/gl_shader_program.hpp"
#include "gfx/default_gl_shaders.hpp"
#include "gfx/shader_type.hpp"

int main() {
    core::SDL2Window window;

    if(!window.initialize("Test Window", glm::vec2(800, 600))) {
		printf("failed to initialize window\n");
        return EXIT_FAILURE;
    }

    gfx::GLRenderer renderer;
   
    if(!renderer.initialize(3, 0, true)) {
        printf("Failed to create GL context\n");
        return false;
    }

    gfx::GLShader vs;
    gfx::GLShader fs;

    vs.createID(gfx::SHADER_TYPE::SHADER_TYPE_VERTEX);
    fs.createID(gfx::SHADER_TYPE::SHADER_TYPE_FRAGMENT);

    if(!vs.loadFromMemory(gfx::defaultFontVertexShader)) {
        return false;
    }
    if(!fs.loadFromMemory(gfx::defaultFontFragmentShader)) {
        return false;
    }

    if(!vs.compile()) {
        return false;
    }
    if(!fs.compile()) {
        return false;
    }

    gfx::GLShaderProgram program;
    program.createID();

    if(!program.attachShader(vs)) {
        return false;
    }
    if(!program.attachShader(fs)) {
        return false;
    }

    if(!program.link()) {
        return false;
    }

    while(window.isOpen()) {
        if(window.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            window.close();
        }
        if(window.isKeyPressed(core::KEYBOARD_KEY::KEY_F11)) {
            window.setFullscreen(true);
        }

        renderer.begin();
        renderer.end();

        window.pollEvents();
        window.swapBuffers();
    }

    vs.deleteID();
    fs.deleteID();
    program.deleteID();
    
    return EXIT_SUCCESS;
}
