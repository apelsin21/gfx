#ifndef RENDERER_TYPE_HPP
#define RENDERER_TYPE_HPP

namespace gfx {
    enum RENDERER_TYPE {
        RENDERER_TYPE_NONE, //no renderer at all
        RENDERER_TYPE_MODERN_OPENGL, //for opengl >= 3.0
        RENDERER_TYPE_LEGACY_OPENGL, //for opengl < 3.0

        RENDERER_TYPE_COUNT //for bounds checking purposes
    };
}

#endif //RENDERER_TYPE_HPP
