#include <stdio.h>
#include <tuple>
#include <exception>

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
    gfx::GLShader vs;
    gfx::GLShader fs;
    gfx::GLShaderProgram program;
    gfx::FreeTypeFont font;

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
    } catch(const std::runtime_error& e) {
        printf("error occurred: %s", e.what());
        return EXIT_FAILURE;
    }

    while(renderer.isOpen()) {
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            renderer.close();
        }
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_F11)) {
            renderer.setFullscreen(!renderer.isFullscreen());
        }
        if(renderer.isKeyPressed(core::KEYBOARD_KEY::KEY_F3)) {
            printf("clipboard contains: %s\n", renderer.getClipboardString().c_str());
        }

        renderer.begin();
        renderer.end();

        switch(renderer.pollEvents()) {
            case gfx::RENDERER_EVENT::RENDERER_EVENT_RESIZED:
                printf("resized\n");
            break;
            case gfx::RENDERER_EVENT::RENDERER_EVENT_NONE:
            break;
            default:
                printf("unhandled renderer event: %s\n", gfx::rendererEventToString(renderer.pollEvents()).c_str());
                break;
        }
        renderer.swapBuffers();
    }

    vs.deleteID();
    fs.deleteID();
    program.deleteID();

    return EXIT_SUCCESS;
}
