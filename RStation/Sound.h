#ifndef _SOUND_H_
#define _SOUND_H_

#include "RStation.h"
#include "Actor.h"
#include "AudioManager.h"

class Sound : public Actor
{
public:
	Sound();
	virtual ~Sound();
	
	void DrawBase() {}
	
	void deleteBuffers();
	void Load(std::string _path);
	void Play();
	void Update(float deltaTime);
	
	void Loop(bool _loop) { sd_loop = _loop; }
	void Volume(float _volume) { sd_volume = _volume; }
	void Pitch(float _pitch) { sd_pitch = _pitch; }
	void Pan(float _pan) { sd_pan = _pan; }
	
private:
	SoundData* sd_sound;
	bool sd_loop, sd_waiting;
	float sd_pan, sd_pitch, sd_volume;
};

#endif
