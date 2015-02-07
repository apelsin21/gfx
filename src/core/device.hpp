#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <iostream>
#include <memory>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "core/windowtype.hpp"
#include "core/sdl2window.hpp"
#include "core/window.hpp"

#include "gfx/renderertype.hpp"
#include "gfx/renderer.hpp"
#include "gfx/modernopenglrenderer.hpp"

namespace core {
    class Device{
        protected:
            gfx::RENDERER_TYPE rendererType; //what type of renderer this device will use
            WINDOW_TYPE windowType; //what type of window this device will use
        
            std::shared_ptr<Window> pWindow;
            std::shared_ptr<gfx::Renderer> pRenderer;
        public:
            Device();
            ~Device();

            std::shared_ptr<Window> createWindow(WINDOW_TYPE);
            std::shared_ptr<Window> getWindow(); //gets an already created window
            WINDOW_TYPE getWindowType();
           
            std::shared_ptr<gfx::Renderer> createRenderer(gfx::RENDERER_TYPE);
            std::shared_ptr<gfx::Renderer> getRenderer();
            gfx::RENDERER_TYPE getRendererType();
    };
}

#endif //DEVICE_HPP
