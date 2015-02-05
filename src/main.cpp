#include <iostream>
#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/device.hpp"

#include "gfx/drivertype.hpp"
#include "gfx/windowtype.hpp"
#include "gfx/windowevent.hpp"
#include "gfx/keyboardkeys.hpp"

using namespace core;
using namespace gfx;
using namespace std;
using namespace glm;

int main(void) {
    shared_ptr<Device> device(make_shared<Device>(DRIVER_TYPE::DRIVER_TYPE_MODERN_OPENGL));

    shared_ptr<Window> window = device->createWindow(WINDOW_TYPE::WINDOW_TYPE_SDL2, "Test Window", vec2(800, 600));

    while(window->isOpen()) {
        if(window->isKeyPressed(KEYBOARD_KEY::KEY_ESCAPE)) {
            window->close();
        }

        window->pollEvents();
        window->swapBuffers();
    }

    return 0;
}
