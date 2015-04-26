#ifndef RENDERER_EVENT_HPP
#define RENDERER_EVENT_HPP

#include <string>

namespace gfx {
    enum RENDERER_EVENT {
        RENDERER_EVENT_NONE,
        RENDERER_EVENT_SHOWN,
        RENDERER_EVENT_HIDDEN,
        RENDERER_EVENT_EXPOSED,
        RENDERER_EVENT_MOVED,
        RENDERER_EVENT_RESIZED,
        RENDERER_EVENT_MINIMIZED,
        RENDERER_EVENT_MAXIMIZED,
        RENDERER_EVENT_RESTORED,
        RENDERER_EVENT_ENTER,
        RENDERER_EVENT_LEAVE,
        RENDERER_EVENT_FOCUS_GAINED,
        RENDERER_EVENT_FOCUS_LOST,
        RENDERER_EVENT_CLOSE,
    };

    static std::string rendererEventToString(RENDERER_EVENT e) {
        switch(e) {
            case RENDERER_EVENT_NONE:
                return "RENDERER_EVENT_NONE";
            break;
            case RENDERER_EVENT_SHOWN:
                return "RENDERER_EVENT_SHOWN";
            break;
            case RENDERER_EVENT_HIDDEN:
                return "RENDERER_EVENT_SHOWN";
            break;
            case RENDERER_EVENT_EXPOSED:
                return "RENDERER_EVENT_EXPOSED";
            break;
            case RENDERER_EVENT_MOVED:
                return "RENDERER_EVENT_MOVED";
            break;
            case RENDERER_EVENT_RESIZED:
                return "RENDERER_EVENT_RESIZED";
            break;
            case RENDERER_EVENT_MINIMIZED:
                return "RENDERER_EVENT_MINIMIZED";
            break;
            case RENDERER_EVENT_MAXIMIZED:
                return "RENDERER_EVENT_MAXIMIZED";
            break;
            case RENDERER_EVENT_RESTORED:
                return "RENDERER_EVENT_RESTORED";
            break;
            case RENDERER_EVENT_ENTER:
                return "RENDERER_EVENT_ENTER";
            break;
            case RENDERER_EVENT_LEAVE:
                return "RENDERER_EVENT_LEAVE";
            break;
            case RENDERER_EVENT_FOCUS_GAINED:
                return "RENDERER_EVENT_GAINED";
            break;
            case RENDERER_EVENT_FOCUS_LOST:
                return "RENDERER_EVENT_LOST";
            break;
            case RENDERER_EVENT_CLOSE:
                return "RENDERER_EVENT_CLOSE";
            break;
            default:
                return "RENDERER_EVENT_NONE";
            break;
        }
    }
}

#endif //RENDERER_EVENT_HPP
