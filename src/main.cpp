#include "game/game.hpp"

int main() {
	mg::Game game;

	if(!game.load()) {
		printf("Game failed to load!\n");
		return -1;
	}
	game.run();

	return 0;
}
