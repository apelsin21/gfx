#include "core/device.hpp"

core::Device::Device(gfx::DRIVER_TYPE type) {
    this->driverType = type;
}
core::Device::~Device() { 
}

gfx::DRIVER_TYPE core::Device::getDriverType() {
    return this->driverType;
}

gfx::Window* core::Device::createWindow(gfx::WINDOW_TYPE type, const std::string& title, const glm::vec2& res) {
    this->windowType = type;

    gfx::Window* window;

    switch(this->windowType) {
        case gfx::WINDOW_TYPE::WINDOW_TYPE_SDL2:
            window = new gfx::SDL2Window();
            break;
        default:
            break;
    }

    if(!window->initialize(title, res)) {
        std::cout << "window failed to initialize\n";
    }

    return window;
}
