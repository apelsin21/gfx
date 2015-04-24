#include <stdio.h>
#include <tuple>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/keyboard_keys.hpp"

#include "gfx/free_image_texture.hpp"
#include "gfx/free_type_font.hpp"
#include "gfx/gl_renderer.hpp"
#include "gfx/gl_shader.hpp"
#include "gfx/gl_shader_program.hpp"
#include "gfx/default_gl_shaders.hpp"
#include "gfx/shader_type.hpp"
#include "gfx/renderer_event.hpp"

int main() {
    gfx::GLRenderer renderer;
   
    if(!renderer.initialize("WINDOW", 3, 0, true)) {
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

    while(renderer.isOpen()) {
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            renderer.close();
        }
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_F11)) {
            renderer.setFullscreen(true);
        }

        renderer.begin();
        renderer.end();

        renderer.pollEvents();
        renderer.swapBuffers();
    }

    vs.deleteID();
    fs.deleteID();
    program.deleteID();
    
    return EXIT_SUCCESS;
}
