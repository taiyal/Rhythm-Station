#ifdef __APPLE__
	#include <OpenAL/al.h>
	#include <OpenAL/alc.h>
#else
	#include <al/al.h>
	#include <al/alc.h>
#endif

#include "AudioManager.h"
#include <stdio.h>

namespace Audio
{
	ALCdevice* device;
	ALCcontext* context;
	void Open()
	{
		device = alcOpenDevice(NULL); // open default device.
		if( !device )
			return;

		context = alcCreateContext(device, NULL);
		alcMakeContextCurrent(context);

		alGetError();
	}

	void Close()
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
	}
} // audio
