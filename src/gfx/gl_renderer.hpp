#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

#include "gfx/color.hpp"
#include "gfx/renderer.hpp"
#include "gfx/renderer_event.hpp"
#include "gfx/gl_shader.hpp"
#include "gfx/gl_shader_program.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <stdio.h>
#include <tuple>
#include <stdexcept>

#include <SDL2/SDL.h>

namespace gfx {
    class GLRenderer : public Renderer {
        protected:
            Color clearColor;
            SDL_Window* _pSdlWindow;
            SDL_GLContext _sdlContext;
            SDL_Event _sdlEvent;

            unsigned int _sdlWindowID;
            const unsigned char* _pSdlKeyboardState;
        public:
            unsigned int majorVersion, minorVersion;
            bool coreProfile;
            GLShaderProgram textShaderProgram;

            GLRenderer();
            ~GLRenderer();

            void setClearColor(const Color&);
            Color getClearColor();

            std::tuple<unsigned int, unsigned int> getSupportedGLVersion();
            bool isGLVersionSupported(unsigned int, unsigned int);

            bool initialize(const std::string&, unsigned int, unsigned int, bool);

            void begin();
            void drawText(const Font&, const std::string&, const glm::vec2&);
            void end();

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

            std::string getClipboardString();
            bool setClipboardString(const std::string&);

            RENDERER_EVENT pollEvents();

            void swapBuffers();
    
            SDL_Scancode convertKeyToSDLScancode(core::KEYBOARD_KEY gfxKey);
    };
}

#endif //OPENGL_RENDERER_HPP
