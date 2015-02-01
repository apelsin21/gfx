#include "core/device.hpp"

core::Device::Device(gfx::DRIVER_TYPE type) {
    this->driverType = type;
}
core::Device::~Device() { 
}

gfx::DRIVER_TYPE core::Device::getDriverType() {
    return this->driverType;
}
