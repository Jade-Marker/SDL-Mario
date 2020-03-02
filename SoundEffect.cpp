#include "SoundEffect.h"

SoundEffect::SoundEffect():
	sound(nullptr)
{
}

SoundEffect::~SoundEffect()
{
	if (sound != nullptr)
	{
		Mix_FreeChunk(sound);
		sound = nullptr;
	}
}

void SoundEffect::Play(int loops)
{
	Mix_PlayChannel(-1, sound, loops);
}

void SoundEffect::Stop()
{
}

bool SoundEffect::Load(std::string path)
{
	sound = Mix_LoadWAV(path.c_str());
	if (sound == nullptr)
	{
		std::cout << "Failed to load " << path << " Error: " << Mix_GetError();
		return false;
	}
	return true;
}
