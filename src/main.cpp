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

int main(void) {
    core::SDL2Window window;

    if(!window.initialize("Test Window", glm::vec2(800, 600))) {
            return EXIT_FAILURE;
    }

    gfx::FreeImageTexture tex;
    
    if(!tex.load("test.png")) {
            std::cout << "failed to load tex\n";
            return EXIT_FAILURE;
    }

    printf("loaded %s, res:{%dx%d}, bpp:%d\n", tex.path.c_str(), tex.width, tex.height, tex.bpp);
    

    while(window.isOpen()) {
        if(window.isKeyPressed(core::KEYBOARD_KEY::KEY_ESCAPE)) {
            window.close();
        }

        window.pollEvents();
        window.swapBuffers();
    }
    
    return EXIT_SUCCESS;
}
