#ifndef MOUSE_KEYS_HPP
#define MOUSE_KEYS_HPP

namespace core {
    enum MOUSE_KEY {
        MOUSE_LEFT, //the standard left mouse button
        MOUSE_MIDDLE, //click down on the scroll wheel or the actual middle button on mostly older mice
        MOUSE_RIGHT, //the standard right mouse button

        MOUSE_EXTRA_1, //the key which most prominently used for next page when web browsing
        MOUSE_EXTRA_2, //the key which goes back in a web browser

        MOUSE_COUNT //used for bounds checking
    };
}

#endif //MOUSE_KEYS_HPP
