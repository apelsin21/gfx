#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

#include <glm/glm.hpp>

namespace mg {
	class Window {
		protected:
		public:
            virtual std::string getCaption() = 0;
            virtual void setCaption(const std::string&) = 0;
			
            virtual glm::vec2 getResolution() = 0;
            virtual void setResolution(const glm::vec2&) = 0;

            virtual glm::vec2 getPosition() = 0;
            virtual void setPosition(const glm::vec2&) = 0;

			virtual bool isFullscreen() = 0;
			virtual bool isFocused() = 0;

            virtual void swapBuffers() = 0;
	};
}

#endif //WINDOW_HPP
