#include <iostream>

#include "core/device.hpp"
#include "gfx/drivertypes.hpp"

int main(void) {
    core::Device* device = new core::Device(gfx::DRIVER_TYPE::OPENGL);

    std::cout << "device driver type: " << device->getDriverType() << "\n";
    
    device->drop();
    
    return 0;
}
