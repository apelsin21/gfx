#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "core/device.hpp"

#include "gfx/drivertype.hpp"
#include "gfx/windowtype.hpp"
#include "gfx/windowevent.hpp"

int main(void) {
    core::Device* device = new core::Device(gfx::DRIVER_TYPE::DRIVER_TYPE_MODERN_OPENGL);

    gfx::Window* window = device->createWindow(gfx::WINDOW_TYPE::WINDOW_TYPE_SDL2, "Test Window", glm::vec2(800, 600));

    while(window->isOpen()) {
        std::cout << "Got window event: " << window->pollEvents() << "\n";
        
        window->swapBuffers();
    }

    window->drop();
    device->drop();
 
    return 0;
}
