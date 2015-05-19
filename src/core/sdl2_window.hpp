#ifndef SDL2_WINDOW_HPP
#define SDL2_WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "core/window.hpp"

#include "gfx/context_settings.hpp"

namespace mg {
class SDL2Window : public Window {
    protected:
		SDL_Window* _pSdlWindow;
        SDL_GLContext _sdlContext;
        SDL_Event _sdlEvent;
        unsigned int _sdlWindowID;
    public:
        SDL2Window();
        ~SDL2Window();

		bool init(const std::string&, int, int, const ContextSettings&);

        std::string getTitle();
        bool setTitle(const std::string&);

		int getWidth();
		int getHeight();
		void setResolution(int, int);
        
		int getPositionX();
		int getPositionY();
        void setPosition(int, int);

        bool isOpen();
        void close(); 

        bool isFullscreen();
        void setFullscreen();
        void setBorderlessFullscreen();
        void setWindowed();

        bool isMaximized();
        bool setMaximized(bool);

        bool isHidden();
        bool setHidden(bool);

        bool isFocused();
        bool setFocused(bool);

        std::string getClipboardString();
        bool setClipboardString(const std::string&);

        void swapBuffers();
};
}

#endif //SDL2_WINDOW_HPP
