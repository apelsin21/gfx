#ifndef SOUND_HPP
#define SOUND_HPP

#include <string>

#include <opus/opusfile.h>

#include <AL/al.h>

namespace mg {
	class Sound {
		protected:
			ALuint buffer;

			std::string opusErrorToString(int);
			bool getError(const char*, int);
		public:
			Sound();
			~Sound();

			bool load(const std::string&);

			unsigned int getBuffer();
	};
}

#endif //SOUND_HPP
