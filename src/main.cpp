#include <iostream>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "core/device.hpp"
#include "gfx/drivertype.hpp"
#include "gfx/windowtype.hpp"

#include <SDL2/SDL.h>

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
        std::cout << "window is open!\n";
        SDL_Delay(2000);

        if(!window->setPosition(glm::vec2(1680, 1050))) {
            std::cout << "failed to set window position!\n";
        }
        
        SDL_Delay(2000);
    }

    window->drop();
    device->drop();
 
    return 0;
}
