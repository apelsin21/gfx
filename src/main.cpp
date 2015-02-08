#include <iostream>
#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/device.hpp"
#include "core/windowtype.hpp"
#include "core/windowevent.hpp"
#include "core/keyboardkeys.hpp"

#include "gfx/renderertype.hpp"

using namespace core;
using namespace gfx;
using namespace std;
using namespace glm;

int main(void) {
    shared_ptr<Device> device(make_shared<Device>());

    shared_ptr<Window> window = device->createWindow(WINDOW_TYPE::WINDOW_TYPE_SDL2);

    if(!window) {
        std::cerr << "failed to create window!\n";
        return -1;
    }

    if(!window->initialize("test window", glm::vec2(800, 600))) {
        std::cerr << "failed to initialize window!\n";
        return -1;
    }

    std::cout << "created a window, info:"
        << "\ntype: " << device->getWindowType()
        << "\nresolution: " << window->getResolution().x << "x" << window->getResolution().y
        << "\ntitle: " << window->getTitle()
        << "\n";
	
    shared_ptr<Renderer> renderer = device->createRenderer(RENDERER_TYPE::RENDERER_TYPE_MODERN_OPENGL);
    
    if(!renderer) {
        std::cerr << "failed to create renderer!\n";
        return -1;
    }

    std::cout << "created a renderer\n";

    while(window->isOpen()) {
        if(window->isKeyPressed(KEYBOARD_KEY::KEY_ESCAPE)) {
            window->close();
        }

        window->pollEvents();
        window->swapBuffers();
    }
    
    return 0;
}
