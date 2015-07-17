#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace mg {
	enum class WINDOW_EVENT {
		CLOSED,
		ENTERED,
		LEFT,
		MINIMIZED, 
		MAXIMIZED,
		SHOWN,
		HIDDEN,
		EXPOSED,
		MOVED,
		RESIZED,
		FOCUS_GAINED,
		FOCUS_LOST,
		RESTORED,
		NOTHING,
	};

	class Window {
		protected:
			std::vector<mg::WINDOW_EVENT> events;
		public:
            virtual std::string getCaption() = 0;
            virtual void setCaption(const std::string&) = 0;
			
            virtual glm::vec2 getResolution() = 0;
            virtual void setResolution(const glm::vec2&) = 0;

            virtual glm::vec2 getPosition() = 0;
            virtual void setPosition(const glm::vec2&) = 0;

			virtual bool isFullscreen() = 0;
			virtual bool isFocused() = 0;

			virtual	unsigned int getNumEvents() = 0;
			virtual	mg::WINDOW_EVENT getEvent() = 0;

			virtual void pollEvents() = 0;
            virtual void swapBuffers() = 0;
	};
}

#endif //WINDOW_HPP
