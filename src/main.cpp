#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stdio.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/sdl2_window.hpp"
#include "core/window_event.hpp"
#include "core/keyboard_keys.hpp"

#include "gfx/free_image_texture.hpp"
#include "gfx/free_type_font.hpp"

int main() {
    core::SDL2Window window;

    if(!window.initialize("Test Window", glm::vec2(800, 600))) {
            return EXIT_FAILURE;
    }

    gfx::FreeImageTexture tex;
    
    if(!tex.load("test.png")) {
            std::cout << "failed to load texture " << tex.path << "\n";
            return EXIT_FAILURE;
    }

    gfx::FreeTypeFont font;
    
    if(!font.load("./test.ttf", 12)) {
        std::cout << "failed to load font " << font.path << "\n";
        return EXIT_FAILURE;
    }

    while(window.isOpen()) {
        if(window.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            window.close();
        }

        window.pollEvents();
        window.swapBuffers();
    }
    
    return EXIT_SUCCESS;
}
