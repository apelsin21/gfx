#include "game/game.hpp"

int main() {
	mg::Game game;

	if(!game.load()) {
		return -1;
	}
	game.run();

	return 0;
}
