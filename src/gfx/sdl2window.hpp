#ifndef SDL2_WINDOW_HPP
#define SDL2_WINDOW_HPP

#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <SDL2/SDL.h>

#include "gfx/window.hpp"

namespace gfx {
    class SDL2Window : public Window {
        private:
            SDL_Window* _pSdlWindow;
        public:
            SDL2Window();
            ~SDL2Window();
    
            bool initialize(const std::string&, const glm::vec2&);
            bool isInitialized();

            std::string getTitle();
            bool setTitle(const std::string&);

            glm::vec2 getResolution();
            bool setResolution(const glm::vec2&);
            
            glm::vec2 getPosition();
            bool setPosition(const glm::vec2&);

            bool isOpen();
            bool close(); 

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
