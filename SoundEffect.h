#pragma once

#include <SDL_mixer.h>

#include <string>
#include <iostream>

class SoundEffect
{
private:
	Mix_Chunk* sound;

public:
	SoundEffect();
	~SoundEffect();

	void Play(int loops);
	void Stop();

	bool Load(std::string path);
};

