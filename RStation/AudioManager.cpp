#ifdef __APPLE__
	#include <OpenAL/al.h>
	#include <OpenAL/alc.h>
#else
	#include <AL/al.h>
	#include <AL/alc.h>
#endif

#include "RStation.h"
#include "AudioManager.h"
#include <stdio.h>

ALCdevice* device;
ALCcontext* context;

std::vector<SoundData*> vpSounds;

SoundData::SoundData()
{
	alGenBuffers(1, this->buffer);
	alGenSources(1, this->source);
	this->error = alGetError();
}

SoundData::~SoundData()
{
	alDeleteBuffers(1, this->buffer);
	alDeleteSources(1, this->source);
}

void SoundData::Register()
{
	Audio::AddSound(this);
}

void Audio::AddSound(SoundData *_sound)
{
	vpSounds.push_back(_sound);
}

void Audio::Clear()
{
	while(!vpSounds.empty())
	{
		delete vpSounds.back();
		vpSounds.pop_back();
	}
}

void Audio::Open()
{
	// open default device.
	device = alcOpenDevice(NULL);
	if( !device )
		return;

	// create device context
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);

	// clear errors
	alGetError();
}

void Audio::Close()
{
	Clear();
	// clean up
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}
