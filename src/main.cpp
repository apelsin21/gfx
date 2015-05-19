#include <stdio.h>
#include <memory>
#include <exception>
#include <iostream>

#include "core/engine.hpp"
#include "core/sdl2_window.hpp"

#include "gfx/context_settings.hpp"

int main() {
	std::shared_ptr<mg::Engine> engine;
	std::shared_ptr<mg::SDL2Window> window;

    try {
        engine = std::make_shared<mg::Engine>();
		window = engine->get<mg::SDL2Window>();

		window->init("Test", 800, 600, mg::ContextSettings(2, 1, 24, false, true, false));
    } catch(const std::runtime_error& e) {
        printf("ERR: %s", e.what());
        return -1;
    }

	while(window->isOpen()) {
		if(std::cin.peek()) {
			window->close();
		}

		window->swapBuffers();
    }

    return 0;
}
