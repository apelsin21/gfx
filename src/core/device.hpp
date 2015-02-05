#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <iostream>
#include <memory>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "gfx/drivertype.hpp"
#include "gfx/windowtype.hpp"
#include "gfx/sdl2window.hpp"
#include "gfx/window.hpp"

namespace core {
    class Device{
        protected:
            gfx::DRIVER_TYPE driverType; //what type of driver this device will use
            gfx::WINDOW_TYPE windowType; //what type of window this device will use
        
            std::shared_ptr<gfx::Window> pWindow;
        public:
            Device(gfx::DRIVER_TYPE);
            ~Device();

            gfx::DRIVER_TYPE getDriverType();
   
            //get a window that was supported when building
            std::shared_ptr<gfx::Window> createWindow(gfx::WINDOW_TYPE, const std::string&, const glm::vec2&);
    };
}

#endif //DEVICE_HPP
