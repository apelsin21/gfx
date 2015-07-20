#include "game/game.hpp"

#include "AL/alc.h"
#include "AL/al.h"
#include "AL/alut.h"

bool getError(int line) {
	ALenum error = alGetError();

	if(error != AL_NO_ERROR) {
		printf("OpenAL error on line %u:\n", line);
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

int main() {
	ALCdevice* device = alcOpenDevice(NULL);
	ALCcontext* context;

	if(device != NULL) {
		context = alcCreateContext(device, NULL);

		if(context != NULL) {
			alcMakeContextCurrent(context);
		}
	}

	if(getError(__LINE__)) {
		return false;
	}

	ALuint buffer, source;

	alGenBuffers(1, &buffer);
	alGenSources(1, &source);

	if(getError(__LINE__)) {
		return false;
	}

	ALfloat listenerPos[] = {0.0f, 0.0f, 0.0f};
	ALfloat listenerVel[] = {0.0f, 0.0f, 0.0f};
	ALfloat listenerOri[] = {0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f};

	ALfloat sourcePos[] = {-2.0, 0.0, 0.0};
	ALfloat sourceVel[] = { 0.0, 0.0, 0.0};

	ALuint environment;

	ALsizei size, freq;
	ALenum format;
	ALvoid* data;
	ALboolean loop = (ALboolean)0;

	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);

	if(getError(__LINE__)) {
		return false;
	}

	const char* file = "test.wav";

	alutLoadWAVFile((ALbyte*)file, &format, &data, &size, &freq, &loop);
	alBufferData(buffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	if(getError(__LINE__)) {
		return false;
	}

	alSourcef(source, AL_PITCH, 1.0f);
	alSourcef(source, AL_GAIN, 1.0f);
	alSourcefv(source, AL_POSITION, sourcePos);
	alSourcefv(source, AL_VELOCITY, sourceVel);
	alSourcef(source, AL_BUFFER, buffer);
	alSourcef(source, AL_LOOPING, AL_TRUE);

	alSourcePlay(source);

	if(getError(__LINE__)) {
		return false;
	}

	mg::Game game;

	if(!game.load()) {
		printf("Game failed to load!\n");
		return -1;
	}
	game.run();

	if(alIsBuffer(buffer)) {
		alDeleteBuffers(1, &buffer);
	}
	if(getError(__LINE__)) {
		return false;
	}

	if(alIsSource(source)) {
		alDeleteSources(1, &source);
	}

	if(getError(__LINE__)) {
		return false;
	}

	alcDestroyContext(context);
	alcCloseDevice(device);

	return 0;
}
