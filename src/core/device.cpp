#include "core/device.hpp"

core::Device::Device(gfx::DRIVER_TYPE type) {
    this->driverType = type;
}
core::Device::~Device() { 
}

gfx::DRIVER_TYPE core::Device::getDriverType() {
    return this->driverType;
}

std::shared_ptr<core::Window> core::Device::createWindow(core::WINDOW_TYPE type, const std::string& title, const glm::vec2& res) {
    this->windowType = type;

    switch(this->windowType) {
        case core::WINDOW_TYPE::WINDOW_TYPE_SDL2:
            this->pWindow = std::make_shared<core::SDL2Window>();
            break;
        default:
            break;
    }

    if(!this->pWindow->initialize(title, res)) {
        std::cout << "window failed to initialize\n";
    }

    return this->pWindow;
}
std::shared_ptr<core::Window> core::Device::getWindow() {
    return this->pWindow;
}
