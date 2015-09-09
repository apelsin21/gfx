#include <stdio.h>

#include "game/game.hpp"

int main(void) {
	mg::Game game;

	if(!game.load()) {
		return -1;
	}

	if(!game.run()) {
		return false;
	}

	return 0;
}
