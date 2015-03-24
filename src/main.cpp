#include <iostream>
#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/window.hpp"
#include "core/windowevent.hpp"
#include "core/keyboardkeys.hpp"

#include "gfx/renderer.hpp"
#include "gfx/texture.hpp"


int main(void) {
    core::Window window("test window", glm::vec2(800, 600));
    gfx::Renderer renderer();
    
    while(window.isOpen()) {
        if(window.isKeyPressed(KEYBOARD_KEY::KEY_ESCAPE)) {
            window.close();
        }

        window.pollEvents();
        window.swapBuffers();
    }
    
    return 0;
}
