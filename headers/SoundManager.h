#pragma once
#include <irrKlang.h>

using namespace irrklang;

class SoundManager {
private:
	ISoundEngine* soundEngine;
	static SoundManager* instance;
	float volume;
	SoundManager();
	~SoundManager();
public:
	static SoundManager* getInstance();
	ISound* playOnce(const char* filepath);
	ISound* playInLoop(const char* filepath);
	void stopPlaying();
	void changeVolume(float value);
	bool drop();
};

