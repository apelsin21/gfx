#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "core/device.hpp"
#include "gfx/drivertype.hpp"
#include "gfx/windowtype.hpp"

int main(void) {
    core::Device* device = new core::Device(gfx::DRIVER_TYPE::OPENGL);

    gfx::Window* window = device->createWindow(gfx::WINDOW_TYPE::SDL2, "Test Window", glm::vec2(800, 600));

    if(window == nullptr) {
        std::cout << "window is nullptr\n";
    }
    if(!window->isInitialized()) {
        std::cout << "window isn't initialized\n";
    }

    if(window->isOpen()) {
        window->swapBuffers();
    
        window->close();
    }

    window->drop();
    device->drop();
 
    return 0;
}
