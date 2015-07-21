#include "game/game.hpp"

#include "sound/sound_player.hpp"
#include "sound/sound.hpp"


int main() {
	mg::SoundPlayer player;
	mg::Sound sound;

	if(!player.initialize()) {
		printf("soundplayer failed to initialize.\n");
		return false;
	}

	if(!sound.load("data/sounds/test.opus")) {
		printf("failed to load sound.\n");
		return false;
	}

	if(!player.playSound(sound, glm::vec3(0.0f, 0.0f, 0.0f))) {
		printf("failed to play sound.\n");
		return false;
	}

	mg::Game game;

	if(!game.load()) {
		printf("Game failed to load!\n");
		return -1;
	}
	game.run();

	return 0;
}
