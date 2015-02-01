#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "core/referencecounted.hpp"

#include "gfx/drivertypes.hpp"

namespace core {
    class Device : public ReferenceCounted {
        protected:
            gfx::DRIVER_TYPE driverType; //what type of driver this device will use

            //gfx::Driver* pdriver; //pointer to active driver
            //gfx::Window* pwindow; //pointer to active window
        public:
            Device(gfx::DRIVER_TYPE);
            ~Device();

            gfx::DRIVER_TYPE getDriverType();
    };
}

#endif //DEVICE_HPP
