#include "game/game.hpp"

int main(void) {
	mg::Game game;

	if(!game.load()) {
		return -1;
	}

	game.run();

	return 0;
}
