#ifndef GRAPHICS_DEVICE_EVENT_HPP
#define GRAPHICS_DEVICE_EVENT_HPP

#include <string>

namespace mg {
    enum GRAPHICS_DEVICE_EVENT {
        GRAPHICS_DEVICE_EVENT_NONE,
        GRAPHICS_DEVICE_EVENT_SHOWN,
        GRAPHICS_DEVICE_EVENT_HIDDEN,
        GRAPHICS_DEVICE_EVENT_EXPOSED,
        GRAPHICS_DEVICE_EVENT_MOVED,
        GRAPHICS_DEVICE_EVENT_RESIZED,
        GRAPHICS_DEVICE_EVENT_MINIMIZED,
        GRAPHICS_DEVICE_EVENT_MAXIMIZED,
        GRAPHICS_DEVICE_EVENT_RESTORED,
        GRAPHICS_DEVICE_EVENT_ENTER,
        GRAPHICS_DEVICE_EVENT_LEAVE,
        GRAPHICS_DEVICE_EVENT_FOCUS_GAINED,
        GRAPHICS_DEVICE_EVENT_FOCUS_LOST,
        GRAPHICS_DEVICE_EVENT_CLOSE,
    };

    static std::string graphicsDeviceEventToString(GRAPHICS_DEVICE_EVENT e) {
        switch(e) {
            case GRAPHICS_DEVICE_EVENT_NONE:
                return "GRAPHICS_DEVICE_EVENT_NONE";
            break;
            case GRAPHICS_DEVICE_EVENT_SHOWN:
                return "GRAPHICS_DEVICE_EVENT_SHOWN";
            break;
            case GRAPHICS_DEVICE_EVENT_HIDDEN:
                return "GRAPHICS_DEVICE_EVENT_SHOWN";
            break;
            case GRAPHICS_DEVICE_EVENT_EXPOSED:
                return "GRAPHICS_DEVICE_EVENT_EXPOSED";
            break;
            case GRAPHICS_DEVICE_EVENT_MOVED:
                return "GRAPHICS_DEVICE_EVENT_MOVED";
            break;
            case GRAPHICS_DEVICE_EVENT_RESIZED:
                return "GRAPHICS_DEVICE_EVENT_RESIZED";
            break;
            case GRAPHICS_DEVICE_EVENT_MINIMIZED:
                return "GRAPHICS_DEVICE_EVENT_MINIMIZED";
            break;
            case GRAPHICS_DEVICE_EVENT_MAXIMIZED:
                return "GRAPHICS_DEVICE_EVENT_MAXIMIZED";
            break;
            case GRAPHICS_DEVICE_EVENT_RESTORED:
                return "GRAPHICS_DEVICE_EVENT_RESTORED";
            break;
            case GRAPHICS_DEVICE_EVENT_ENTER:
                return "GRAPHICS_DEVICE_EVENT_ENTER";
            break;
            case GRAPHICS_DEVICE_EVENT_LEAVE:
                return "GRAPHICS_DEVICE_EVENT_LEAVE";
            break;
            case GRAPHICS_DEVICE_EVENT_FOCUS_GAINED:
                return "GRAPHICS_DEVICE_EVENT_GAINED";
            break;
            case GRAPHICS_DEVICE_EVENT_FOCUS_LOST:
                return "GRAPHICS_DEVICE_EVENT_LOST";
            break;
            case GRAPHICS_DEVICE_EVENT_CLOSE:
                return "GRAPHICS_DEVICE_EVENT_CLOSE";
            break;
            default:
                return "GRAPHICS_DEVICE_EVENT_NONE";
            break;
        }
    }
}

#endif //GRAPHICS_DEVICE_EVENT_HPP
