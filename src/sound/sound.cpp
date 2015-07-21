#include "sound/sound.hpp"

mg::Sound::Sound() {
	this->buffer = 0;
}
mg::Sound::~Sound() {
	if(alIsBuffer(this->buffer)) {
		alDeleteBuffers(1, &this->buffer);
	}
}

std::string mg::Sound::opusErrorToString(int e) {
	switch(e) {
	case OP_FALSE:
		return "OP_FALSE: A request did not succeed.";
	case OP_HOLE:
		return "OP_HOLE: There was a hole in the page sequence numbers.";
	case OP_EREAD:
		return "OP_EREAD: An underlying read, seek or tell operation failed.";
	case OP_EFAULT:
		return "OP_EFAULT: A NULL pointer was passed where none was expected, or an internal library error was encountered.";
	case OP_EIMPL:
		return "OP_EIMPL: The stream used a feature which is not implemented.";
	case OP_EINVAL:
		return "OP_EINVAL: One or more parameters to a function were invalid.";
	case OP_ENOTFORMAT:
		return "OP_ENOTFORMAT: This is not a valid Ogg Opus stream.";
	case OP_EBADHEADER:
		return "OP_EBADHEADER: A required header packet was not properly formatted.";
	case OP_EVERSION:
		return "OP_EVERSION: The ID header contained an unrecognised version number.";
	case OP_EBADPACKET:
		return "OP_EBADPACKET: An audio packet failed to decode properly.";
	case OP_EBADLINK:
		return "OP_EBADLINK: We failed to find data we had seen before or the stream was sufficiently corrupt that seeking is impossible.";
	case OP_ENOSEEK:
		return "OP_ENOSEEK: An operation that requires seeking was requested on an unseekable stream.";
	case OP_EBADTIMESTAMP:
		return "OP_EBADTIMESTAMP: The first or last granule position of a link failed basic validity checks.";
	default:
		return "Unknown error.";
	}
}
bool mg::Sound::getError(const char* file, int line) {
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

bool mg::Sound::load(const std::string& p) {
	this->getError(__FILE__, __LINE__);

	int error = 0;
	// Open the file.
	OggOpusFile* file = op_open_file(p.c_str(), &error);

	if(error) {
		printf("Failed to open file %s (%d: %s)\n", p.c_str(), error, this->opusErrorToString(error).c_str());
		return error;
	}

	this->getError(__FILE__, __LINE__);

	// Get the number of channels in the current link.
	int num_channels = op_channel_count(file,-1);
	// Get the number of samples (per channel) in the current link.
	int pcm_size = op_pcm_total(file,-1);

	// We only support stereo and mono, set the openAL format based on channels.
	// opus always uses signed 16-bit integers, unless the _float functions are called.
	ALenum format;
	if (num_channels == 1) {
		format = AL_FORMAT_MONO16;
	} else if (num_channels == 2) {
		format = AL_FORMAT_STEREO16;
	} else {
		printf("File contained more channels than we support (%d).\n", num_channels);
		return false;
	}

	// Allocate a buffer big enough to store the entire uncompressed file.
	int16_t* buf = new int16_t[pcm_size*num_channels];

	if(!buf) {
		printf("Could not allocate decode buffer.\n");
		return false;
	}

	int samples_read = 0;

	// Keep reading samples until we have them all.
	while(samples_read < pcm_size) {
		// op_read returns number of samples read (per channel), and accepts number of samples which fit in the buffer, not number of bytes.
		int ns = op_read(file, buf + samples_read*num_channels, pcm_size*num_channels, 0);

		if(ns < 0) {
			printf("Couldn't decode at offset %d: Error %d (%s)\n", samples_read, ns, opusErrorToString(ns).c_str());
			return ns;
		}

		samples_read += ns;
	}

	op_free(file);

	if(alIsBuffer(this->buffer) == AL_FALSE) {
		alGenBuffers(1, &this->buffer);
	}

	this->getError(__FILE__, __LINE__);

	// Send it to OpenAL (which takes bytes).
	alBufferData(this->buffer, format, buf, samples_read*num_channels*2, 48000);

	this->getError(__FILE__, __LINE__);

	return true;
}

unsigned int mg::Sound::getBuffer() {
	return this->buffer;
}
