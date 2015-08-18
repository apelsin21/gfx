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
		fprintf(stderr, "OpenAL error (%s : %u) : ", file, line);
		switch(error) {
		case AL_INVALID_NAME:
			fprintf(stderr, "AL_INVALID_NAME: Invalid name parameter\n");
			break;
		case AL_INVALID_ENUM:
			fprintf(stderr, "AL_INVALID_ENUM: Invalid parameter\n");
			break;
		case AL_INVALID_VALUE:
			fprintf(stderr, "AL_INVALID_VALUE: Invalid enum parameter value\n");
			break;
		case AL_INVALID_OPERATION:
			fprintf(stderr, "AL_INVALID_OPERATION: Illegal call\n");
			break;
		case AL_OUT_OF_MEMORY:
			fprintf(stderr, "AL_OUT_OF_MEMORY: Unable to allocate memory\n");
			break;
		}

		return true;
	}

	return false;
}

bool mg::SoundPlayer::initialize() {
	getError(__FILE__, __LINE__);

	this->device = alcOpenDevice(0);

	getError(__FILE__, __LINE__);

	if(!this->device) {
		fprintf(stderr, "OpenAL error: Couldn't open device.\n");
		return false;
	}

	this->context = alcCreateContext(this->device, 0);

	getError(__FILE__, __LINE__);

	if(!this->context) {
		fprintf(stderr, "OpenAL error: Couldn't open context.\n");
		alcCloseDevice(this->device);
		return false;
	}

	alcMakeContextCurrent(context);

	getError(__FILE__, __LINE__);
	alGenSources(1, &this->source);
	getError(__FILE__, __LINE__);
	alListener3f(AL_POSITION, 0.f, 0.f, 0.f);
	getError(__FILE__, __LINE__);
	alListenerf(AL_GAIN, 1.f);
	getError(__FILE__, __LINE__);

	this->initialized = true;

	return true;
}

bool mg::SoundPlayer::playSound(mg::Sound& sound) {
	if(alIsBuffer(sound.getBuffer()) == AL_FALSE) {
		fprintf(stderr, "Tried to play sound, but got invalid OpenAL buffer.\n");
		return false;
	}	

	getError(__FILE__, __LINE__);

	alSourcei(this->source, AL_BUFFER, sound.getBuffer());
	alSource3f(this->source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcef(this->source, AL_GAIN, 1.0f);

	getError(__FILE__, __LINE__);

	alSourcePlay(this->source);

	getError(__FILE__, __LINE__);

	//int sourceState;
	//do {
	//	alGetSourcei(this->source, AL_SOURCE_STATE, &sourceState);
	//} while(sourceState != AL_STOPPED);

	getError(__FILE__, __LINE__);

	return true;
}

void mg::SoundPlayer::setPosition(const glm::vec3& pos) {
	alListener3f(AL_POSITION, pos.x, pos.y, pos.z);

	this->listenerPosition = pos;
}
