#ifndef DRIVER_TYPE_HPP
#define DRIVER_TYPE_HPP

namespace gfx {
    enum DRIVER_TYPE {
        DRIVER_TYPE_NONE, //no driver at all
        DRIVER_TYPE_MODERN_OPENGL, //for opengl >= 3.0
        DRIVER_TYPE_LEGACY_OPENGL, //for opengl < 3.0

        DRIVER_TYPE_COUNT //for bounds checking purposes
    };
}

#endif //DRIVER_TYPE_HPP
