#ifndef _AUDIO_H_
#define _AUDIO_H_

#ifdef __APPLE__
#include <OpenAL/al.h>
#else
#include <AL/al.h>
#endif

struct SoundData
{
	SoundData();
	virtual ~SoundData();
	void Register();
	
	// buffer and source data, error handle (just in case)
	ALuint buffer[1];
	ALuint source[1];
	ALenum error;
	
	// audio file path
	std::string path;
};

namespace Audio
{
	void AddSound(SoundData *sound);
	void Clear();
	void Open();
	void Close();
}

#endif
