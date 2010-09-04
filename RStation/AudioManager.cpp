#ifdef __APPLE__
	#include <OpenAL/al.h>
	#include <OpenAL/alc.h>
#else
	#include <AL/al.h>
	#include <AL/alc.h>
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
