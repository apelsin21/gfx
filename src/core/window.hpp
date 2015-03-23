#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <SDL2/SDL.h>

#include "core/window.hpp"
#include "core/windowevent.hpp"
#include "core/keyboardkeys.hpp"

namespace core {
    class Window {
        private:
            SDL_Window* _pSdlWindow;
            SDL_GLContext _sdlContext;
            SDL_Event _sdlEvent;

            std::string title;
            glm::vec2 resolution;
            glm::vec2 position;
            bool open, fullscreen, maximized, hidden, focused;

            unsigned int _sdlWindowID;
            const unsigned char* _pSdlKeyboardState;
        public:
            Window(const std::string&, const glm::vec2&);
            ~Window();
    
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

            WINDOW_EVENT pollEvents();
            
            SDL_Scancode convertKeyToSDLScancode(core::KEYBOARD_KEY gfxKey);

            void swapBuffers();
    };
}

#endif //WINDOW_HPP
