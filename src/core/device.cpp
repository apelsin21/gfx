#include "core/device.hpp"

core::Device::Device() {
}
core::Device::~Device() { 
}

std::shared_ptr<core::Window> core::Device::createWindow(core::WINDOW_TYPE type) {
    this->windowType = type;

    switch(this->windowType) {
        case core::WINDOW_TYPE::WINDOW_TYPE_SDL2:
            this->pWindow = std::make_shared<core::SDL2Window>();
            break;
        default:
            break;
    }

    return this->pWindow;
}
std::shared_ptr<core::Window> core::Device::getWindow() {
    return this->pWindow;
}
core::WINDOW_TYPE core::Device::getWindowType() {
    return this->windowType;
}

std::shared_ptr<gfx::Renderer> core::Device::createRenderer(gfx::RENDERER_TYPE type) {
    this->rendererType = type;

    switch(this->rendererType) {
        case gfx::RENDERER_TYPE::RENDERER_TYPE_MODERN_OPENGL:
            this->pRenderer = std::make_shared<gfx::ModernOpenGLRenderer>();
            break;
        default:
            break;
    }

    return this->pRenderer;
}
gfx::RENDERER_TYPE core::Device::getRendererType() {
    return this->rendererType;
}
