#ifndef DRIVER_TYPE_HPP
#define DRIVER_TYPE_HPP

namespace gfx {
    enum DRIVER_TYPE {
        DRIVER_TYPE_NONE,
        DRIVER_TYPE_MODERN_OPENGL, //for opengl versions 3.0 and up
        DRIVER_TYPE_LEGACY_OPENGL //for opengl versions below 3.0
    };
}

#endif //DRIVER_TYPE_HPP
