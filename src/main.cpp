#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <memory>
#include <exception>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "core/keyboard_keys.hpp"

#include "gfx/texture.hpp"
#include "gfx/font.hpp"

#include "gfx/graphics_device.hpp"
#include "gfx/graphics_device_event.hpp"
#include "gfx/context_settings.hpp"

#include "gfx/shader.hpp"
#include "gfx/shader_program.hpp"
#include "gfx/shader_type.hpp"

#include "gfx/sprite_batch.hpp"

int main() {
    mg::Engine engine;
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<GUIManager> guiMgr;
	std::shared_ptr<Window> window;
    mg::ContextSettings settings(3, 3, 24, true, true, false);

    try {
        engine.initialize("Window", glm::vec2(800, 600), settings);

		renderer = engine.getRenderer();
		guiMgr = engine.getGUIManage();
		window = engine.getWindow();

    } catch(const std::runtime_error& e) {
        printf("ERR: %s", e.what());
        return -1;
    }

	while(window->isOpen()) {
		if(window.isKeyPressed(mg::KEYBOARD_KEY::KEY_ESCAPE)) {
			window->close();
		}

        renderer->begin();
		renderer->draw(guiMgr);
		renderer->end();

		window->swapBuffers();
    }

    return 0;
}
