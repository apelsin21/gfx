#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>

#include <glm/glm.hpp>

#include "core/keyboard_keys.hpp"

#include "gfx/font.hpp"
#include "gfx/renderer_event.hpp"

namespace gfx {
    class Renderer {
        protected:
            bool isDrawing;
        public:
            std::string title;
            glm::vec2 resolution;
            glm::vec2 position;
            bool open, fullscreen, maximized, hidden, focused, initialized;

            virtual void begin() = 0;
            virtual void drawText(const gfx::Font&, const std::string&, const glm::vec2&) = 0;
            virtual void end() = 0;

            virtual std::string getTitle() = 0;
            virtual bool setTitle(const std::string&) = 0;

            virtual glm::vec2 getResolution() = 0;
            virtual bool setResolution(const glm::vec2&) = 0;

            virtual glm::vec2 getPosition() = 0;
            virtual bool setPosition(const glm::vec2&) = 0;

            virtual bool isOpen() = 0;
            virtual bool close() = 0; 

            virtual bool isFullscreen() = 0;
            virtual bool setFullscreen(bool) = 0;
            virtual bool setBorderlessFullscreen(bool) = 0;

            virtual bool isMaximized() = 0;
            virtual bool setMaximized(bool) = 0;

            virtual bool isHidden() = 0;
            virtual bool setHidden(bool) = 0;

            virtual bool isFocused() = 0;
            virtual bool setFocused(bool) = 0;

            virtual bool isKeyPressed(core::KEYBOARD_KEY) = 0;

            virtual RENDERER_EVENT pollEvents() = 0;

            virtual void swapBuffers() = 0;
    };
}

#endif //RENDERER_HPP
