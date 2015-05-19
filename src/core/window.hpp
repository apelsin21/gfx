#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <tuple>
#include <stdexcept>

#include "gfx/context_settings.hpp"

namespace mg {
class Window {
    protected:
        bool open, fullscreen, initialized;
		bool maximized, hidden, focused;
		int width, height, x, y;
        std::string title;

		ContextSettings settings;
    public:
        Window();

		virtual bool init(const std::string&, int, int, const ContextSettings&) = 0;

        virtual std::string getTitle() = 0;
        virtual bool setTitle(const std::string&) = 0;

		virtual int getWidth() = 0;
		virtual int getHeight() = 0;
		virtual void setResolution(int, int) = 0;
         
		virtual int getPositionX() = 0;
		virtual int getPositionY() = 0;
        virtual void setPosition(int, int) = 0;

        virtual bool isOpen() = 0;
        virtual void close() = 0; 

        virtual bool isFullscreen() = 0;
        virtual void setFullscreen() = 0;
        virtual void setBorderlessFullscreen() = 0;
        virtual void setWindowed() = 0;

        virtual bool isMaximized() = 0;
        virtual bool setMaximized(bool) = 0;

        virtual bool isHidden() = 0;
        virtual bool setHidden(bool) = 0;

        virtual bool isFocused() = 0;
        virtual bool setFocused(bool) = 0;

        virtual std::string getClipboardString() = 0;
        virtual bool setClipboardString(const std::string&) = 0;

        virtual void swapBuffers() = 0;
};
}
#endif //WINDOW_HPP
