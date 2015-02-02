#include <iostream>

#include "core/device.hpp"
#include "gfx/drivertype.hpp"
#include "gfx/windowtype.hpp"

int main(void) {
    core::Device* device = new core::Device(gfx::DRIVER_TYPE::OPENGL);

    gfx::Window* window = device->createWindow(gfx::WINDOW_TYPE::SDL2);
    
    window->drop();
    device->drop();
    
    return 0;
}
