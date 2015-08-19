#include "game/game.hpp"

#include "gfx/modern_gl_renderer.hpp"
#include "gfx/gl_vertex_buffer.hpp"

int main(void) {
	mg::Game game;

	if(!game.load()) {
		return -1;
	}

	game.run();

	return 0;
}
