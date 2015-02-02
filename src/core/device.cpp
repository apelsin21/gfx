#include "core/device.hpp"

core::Device::Device(gfx::DRIVER_TYPE type) {
    this->driverType = type;
}
core::Device::~Device() { 
}

gfx::DRIVER_TYPE core::Device::getDriverType() {
    return this->driverType;
}

gfx::Window* core::Device::createWindow(gfx::WINDOW_TYPE t) {
    this->windowType = t;

    gfx::Window* window;

    switch(t) {
        case gfx::WINDOW_TYPE::SDL2:
            window = new gfx::SDL2Window();  
            break;
        default:
            break;
    }

    return window;
}
