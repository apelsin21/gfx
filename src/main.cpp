#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "core/device.hpp"

#include "gfx/drivertype.hpp"
#include "gfx/windowtype.hpp"
#include "gfx/windowevent.hpp"
#include "gfx/keyboardkeys.hpp"

int main(void) {
    core::Device* device = new core::Device(gfx::DRIVER_TYPE::DRIVER_TYPE_MODERN_OPENGL);

    gfx::Window* window = device->createWindow(gfx::WINDOW_TYPE::WINDOW_TYPE_SDL2, "Test Window", glm::vec2(800, 600));

    while(window->isOpen()) {
        if(window->isKeyPressed(gfx::KEYBOARD_KEY::KEY_ESCAPE)) {
            window->close();
        }
        if(window->isKeyPressed(gfx::KEYBOARD_KEY::KEY_E)) {
            std::cout << "E\n";
        }
       
        window->pollEvents();
        window->swapBuffers();
    }

    window->drop();
    device->drop();
 
    return 0;
}
