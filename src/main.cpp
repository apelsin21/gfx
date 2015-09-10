#include <enet/enet.h>
#include <cstdio>

#include "game/game.hpp"

int main(void) {
	if(enet_initialize() != 0) {
		printf("An error occurred while initializing ENet.\n");
		return -1;
	}

	mg::Game game;

	if(!game.load()) {
		return -1;
	}

	if(!game.run()) {
		return -1;
	}

	enet_deinitialize();

	return 0;
}
