#ifndef SDL2_WINDOW_HPP
#define SDL2_WINDOW_HPP

#include <iostream>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <SDL2/SDL.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include "core/window.hpp"

namespace core {
    class SDL2Window : public Window {
        private:
            SDL_Window* _pSdlWindow;
            SDL_GLContext _sdlContext;
            SDL_Event _sdlEvent;

            unsigned int _sdlWindowID;
            const unsigned char* _pSdlKeyboardState;
        public:
            SDL2Window();
            ~SDL2Window();

            bool initialize(const std::string&, const glm::vec2&);

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
            bool setBorderlessFullscreen(bool);

            bool isMaximized();
            bool setMaximized(bool);

            bool isHidden();
            bool setHidden(bool);

            bool isFocused();
            bool setFocused(bool);
 
            bool isKeyPressed(core::KEYBOARD_KEY);

            std::string getClipboardString();
            bool setClipboardString(const std::string&);

            WINDOW_EVENT pollEvents();

            void swapBuffers();
    
            SDL_Scancode convertKeyToSDLScancode(core::KEYBOARD_KEY gfxKey);
    };
}

#endif //SDL2_WINDOW_HPP
