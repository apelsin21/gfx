#ifndef SDL2_WINDOW_HPP
#define SDL2_WINDOW_HPP

#include "core/window.hpp"

#include <epoxy/gl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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

            std::string getCaption() const;
            void setCaption(const std::string&);
			
            glm::vec2 getResolution() const;
            void setResolution(const glm::vec2&);

            glm::vec2 getPosition() const;
            void setPosition(const glm::vec2&);

			bool isFullscreen() const;
			bool isMaximized() const;
			bool isFocused() const;

			void grabInput(bool);
			bool isInputGrabbed() const;

			unsigned int getNumEvents() const;
			mg::WINDOW_EVENT getEvent();

			SDL_Window* getSDLHandle() const;

			void pollEvents();
            void swapBuffers();
	};
}

#endif //SDL2_WINDOW_HPP
