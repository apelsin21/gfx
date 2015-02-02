#ifndef SDL2_WINDOW_HPP
#define SDL2_WINDOW_HPP

#include "gfx/window.hpp"

#include <SDL2/SDL.h>

namespace gfx {
    class SDL2Window : public Window {
        public:
            SDL2Window();
            ~SDL2Window();
    
            void initialize();
            bool isInitialized();

            std::string getTitle();
            bool setTitle(const std::string&);

            glm::vec2 getResolution();
            bool setResolution(const glm::vec2&);
            
            glm::vec2 getPosition();
            bool setPosition(const glm::vec2&);

            bool isOpen();
            bool setOpen(bool);

            bool isFullscreen();
            bool setFullscreen(bool);

            bool isMaximized();
            bool setMaximized(bool);

            bool isHidden();
            bool setHidden(bool);

            bool isFocused();
            bool setFocused(bool);
    
            void swapBuffers();
    };
}

#endif //SDL2_WINDOW_HPP
