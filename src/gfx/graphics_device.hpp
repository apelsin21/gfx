#ifndef GRAPHICS_DEVICE_HPP
#define GRAPHICS_DEVICE_HPP

#include <string>
#include <tuple>
#include <stdexcept>
#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/type_aligned.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "core/keyboard_keys.hpp"

#include "gfx/color.hpp"
#include "gfx/graphics_device_event.hpp"
#include "gfx/shader.hpp"
#include "gfx/shader_program.hpp"
#include "gfx/font.hpp"
#include "gfx/texture.hpp"
#include "gfx/context_settings.hpp"
#include "gfx/sprite_batch.hpp"

namespace mg {
    class GraphicsDevice {
        protected:
            Color clearColor;

            SDL_Window* _pSdlWindow;
            SDL_GLContext _sdlContext;
            SDL_Event _sdlEvent;
            unsigned int _sdlWindowID;
            const unsigned char* _pSdlKeyboardState;
        public:
            ShaderProgram spriteShaderProgram;
            bool isDrawing, open, fullscreen, initialized, maximized, hidden, focused;
            mg::ContextSettings contextSettings;
            glm::i32vec2 resolution, position;
            std::string title;
			unsigned int boundTextureID, boundShaderProgramID, fps;
			float deltaTime, lastFrameTime, currentFrameTime;

            GraphicsDevice();
            ~GraphicsDevice();

            void setClearColor(const Color&);
            Color getClearColor();

            bool initialize(const std::string&, const glm::i32vec2&, ContextSettings&);

            std::string getTitle();
            bool setTitle(const std::string&);

            glm::i32vec2 getResolution();
            bool setResolution(const glm::i32vec2&);
            
            glm::i32vec2 getFramebufferSize();
            bool setFramebufferSize(const glm::i32vec2&);

            glm::i32vec2 getPosition();
            bool setPosition(const glm::i32vec2&);

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
 
			bool hasPressedKey();
			std::vector<mg::KEYBOARD_KEY> getPressedKeys();
            bool isKeyPressed(mg::KEYBOARD_KEY);

            std::string getClipboardString();
            bool setClipboardString(const std::string&);

            void pollEvents();
            
            void begin();
            void end();

            void swapBuffers();
    };
}

#endif //GRAPHICS_DEVICE_HPP
