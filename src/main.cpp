#include <iostream>
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

int main() {
    core::SDL2Window window;

    if(!window.initialize("Test Window", glm::vec2(800, 600))) {
		std::cout << "failed to initialize window\n";
        return EXIT_FAILURE;
    }

    gfx::FreeImageTexture tex;
    
    //loads texture from file
    if(!tex.load("test.png")) {
            std::cout << "failed to load texture " << tex.path << "\n";
    }

    gfx::FreeTypeFont font;
    
    //Loads the font from file, generates a texture using the pixelsize specified
    if(!font.load("./test.ttf", 12)) {
        std::cout << "failed to load font " << font.path << "\n";
    }

    gfx::GLRenderer renderer;
   
    //Loads default shaders, creates opengl context, checks if version parameters are supported on the machine
    if(!renderer.initialize(renderer.getSupportedGLVersion(), true)) {
        std::cout << "Failed to create GL context\n";
        return false;
    }

    while(window.isOpen()) {
        if(window.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            window.close();
        }

        switch(window.pollEvents()) {
            case core::WINDOW_EVENT::WINDOW_EVENT_RESIZED:
                window.setResolution(window.getResolution());
                break;
            default:
                break;
        }

        //Clears color buffer, depth buffer (stencil buffer?)
        renderer.begin();
        //draws text using provided font using the default font shader
		//since no other font shader has been specificed, at the coordinates specified
        renderer.drawText(font, "bajs", window.resolution / 2.0f);
        renderer.end();

        window.swapBuffers();
    }
    
    return EXIT_SUCCESS;
}
