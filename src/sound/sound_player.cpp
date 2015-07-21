#include "sound/sound_player.hpp"

mg::SoundPlayer::SoundPlayer() {
	this->initialized = false;
	this->source = 0;

	this->device = nullptr;
	this->context = nullptr;
}
mg::SoundPlayer::~SoundPlayer() {
	if(this->initialized) {
		if(alIsSource(this->source)) {
			alDeleteSources(1, &this->source);
		}

		alcMakeContextCurrent(0);
		alcDestroyContext(this->context);
		alcCloseDevice(this->device);
	}
}

bool mg::SoundPlayer::getError(const char* file, int line) {
	ALenum error = alGetError();

	if(error != AL_NO_ERROR) {
		printf("OpenAL error in file %s, on line %u:\n", file, line);
		switch(error) {
		case AL_INVALID_NAME:
			printf("OpenAL error: AL_INVALID_NAME: Invalid name parameter\n");
			break;
		case AL_INVALID_ENUM:
			printf("OpenAL error: AL_INVALID_ENUM: Invalid parameter\n");
			break;
		case AL_INVALID_VALUE:
			printf("OpenAL error: AL_INVALID_VALUE: Invalid enum parameter value\n");
			break;
		case AL_INVALID_OPERATION:
			printf("OpenAL error: AL_INVALID_OPERATION: Illegal call\n");
			break;
		case AL_OUT_OF_MEMORY:
			printf("OpenAL error: AL_OUT_OF_MEMORY: Unable to allocate memory\n");
			break;
		}

		return true;
	}

	return false;
}

bool mg::SoundPlayer::initialize() {
	getError(__FILE__, __LINE__);

	this->device = alcOpenDevice(NULL);

	getError(__FILE__, __LINE__);

	if(this->device == nullptr) {
		printf("OpenAL error: Couldn't open device.\n");
		return false;
	}

	this->context = alcCreateContext(device, 0);

	getError(__FILE__, __LINE__);

	if(this->context == nullptr) {
		printf("OpenAL error: Couldn't open context.\n");
		alcCloseDevice(this->device);
		return false;
	}

	getError(__FILE__, __LINE__);

	alcMakeContextCurrent(context);

	getError(__FILE__, __LINE__);

	alGenSources(1, &this->source);

	getError(__FILE__, __LINE__);

	this->initialized = true;

	return true;
}

bool mg::SoundPlayer::playSound(mg::Sound& sound, const glm::vec3& pos) {
	ALuint buffer;

	if(alIsBuffer(sound.getBuffer())) {
		buffer = sound.getBuffer();
	} else {
		printf("Tried to play sound, but got invalid OpenAL buffer.\n");
		return false;
	}	

	getError(__FILE__, __LINE__);

	alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	alListenerf(AL_GAIN, 1.0f);

	getError(__FILE__, __LINE__);

	alSourcei(this->source, AL_BUFFER, buffer);

	alSource3f(this->source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcef(this->source, AL_GAIN, 1.0f);

	getError(__FILE__, __LINE__);

	alSourcePlay(this->source);

	getError(__FILE__, __LINE__);

	int sourceState;
	do {
		alGetSourcei(this->source, AL_SOURCE_STATE, &sourceState);
	} while(sourceState != AL_STOPPED);

	getError(__FILE__, __LINE__);

	return true;
}
