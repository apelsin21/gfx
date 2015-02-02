#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "core/referencecounted.hpp"

#include "gfx/drivertype.hpp"
#include "gfx/windowtype.hpp"
#include "gfx/sdl2window.hpp"
#include "gfx/window.hpp"

namespace core {
    class Device : public virtual ReferenceCounted {
        protected:
            gfx::DRIVER_TYPE driverType; //what type of driver this device will use
            gfx::WINDOW_TYPE windowType; //what type of window this device will use

            //gfx::Driver* pdriver; //pointer to active driver
            gfx::Window* pwindow; //pointer to active window
        public:
            Device(gfx::DRIVER_TYPE);
            ~Device();

            gfx::DRIVER_TYPE getDriverType();
    
            gfx::Window* createWindow(gfx::WINDOW_TYPE);
    };
}

#endif //DEVICE_HPP
