#ifndef SDL2_WINDOW_HPP
#define SDL2_WINDOW_HPP

#include "core/window.hpp"

#include <epoxy/gl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdexcept>

namespace mg {
	class SDL2Window : public Window {
		protected:
            SDL_Window* sdlWindow;
            SDL_GLContext sdlContext;
            SDL_Event sdlEvent;
            unsigned int sdlWindowID;
		public:
			SDL2Window();
			~SDL2Window();

            std::string getCaption();
            void setCaption(const std::string&);
			
            glm::vec2 getResolution();
            void setResolution(const glm::vec2&);

            glm::vec2 getPosition();
            void setPosition(const glm::vec2&);

			bool isFullscreen();
			bool isMaximized();
			bool isFocused();

            void swapBuffers();
	};
}

#endif //SDL2_WINDOW_HPP
