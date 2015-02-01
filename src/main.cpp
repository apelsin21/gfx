#include <iostream>

#include "core/device.hpp"
#include "gfx/drivertypes.hpp"

int main(void) {
    core::Device* device = new core::Device(gfx::DRIVER_TYPE::OPENGL);

    const char* typeName = "";

    switch(device->getDriverType()) {
        case gfx::DRIVER_TYPE::NONE:
            typeName = "NONE";
            break;
        case gfx::DRIVER_TYPE::OPENGL:
            typeName = "OPENGL";
            break;
        default:
            typeName = "UNKNOWN";
            break;
    }

    std::cout << "device driver type: " << typeName << "\n";
    
    device->drop();
    
    return 0;
}
