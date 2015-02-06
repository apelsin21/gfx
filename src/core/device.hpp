#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <iostream>
#include <memory>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "core/windowtype.hpp"
#include "core/sdl2window.hpp"
#include "core/window.hpp"

#include "gfx/drivertype.hpp"

namespace core {
    class Device{
        protected:
            gfx::DRIVER_TYPE driverType; //what type of driver this device will use
            core::WINDOW_TYPE windowType; //what type of window this device will use
        
            std::shared_ptr<Window> pWindow;
        public:
            Device(gfx::DRIVER_TYPE);
            ~Device();

            gfx::DRIVER_TYPE getDriverType();
   
            //get a window that was supported when building
            std::shared_ptr<Window> createWindow(WINDOW_TYPE, const std::string&, const glm::vec2&);
            std::shared_ptr<Window> getWindow(); //gets a created window
    };
}

#endif //DEVICE_HPP
