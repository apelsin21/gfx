#ifndef SOUND_PLAYER_HPP
#define SOUND_PLAYER_HPP

#include <AL/alc.h>
#include <AL/al.h>

#include <glm/glm.hpp>

#include "sound/sound.hpp"

namespace mg {
	class SoundPlayer {
		protected:
			ALCdevice* device;
			ALCcontext* context;
			ALuint source;

			bool initialized;
			bool getError(const char*, int);

			glm::vec3 listenerPosition;
		public:
			SoundPlayer();
			~SoundPlayer();

			bool initialize();

			bool playSound(mg::Sound&);

			void setPosition(const glm::vec3&);
	};
}

#endif //SOUND_PLAYER_HPP
