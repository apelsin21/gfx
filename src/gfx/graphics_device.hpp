#ifndef GRAPHICS_DEVICE_HPP
#define GRAPHICS_DEVICE_HPP

#include <tuple>
#include <stdexcept>
#include <chrono>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/type_aligned.hpp>

#include "core/keyboard_keys.hpp"

#include "gfx/shader.hpp"
#include "gfx/shader_program.hpp"
#include "gfx/font.hpp"
#include "gfx/texture.hpp"
#include "gfx/sprite_batch.hpp"

namespace mg {
    class GraphicsDevice {
        protected:
            Color clearColor;

        public:
            ShaderProgram spriteShaderProgram;
            bool isDrawing;
            mg::ContextSettings contextSettings;
			unsigned int boundTextureID, boundShaderProgramID, fps;
			float deltaTime, lastFrameTime, currentFrameTime;

            GraphicsDevice();
            ~GraphicsDevice();

            void setClearColor(const Color&);
            Color getClearColor();

            bool initialize(const std::string&, const glm::i32vec2&, ContextSettings&);
            
            glm::i32vec2 getFramebufferSize();
            bool setFramebufferSize(const glm::i32vec2&);

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

            void begin();
            void end();
    };
}

#endif //GRAPHICS_DEVICE_HPP
