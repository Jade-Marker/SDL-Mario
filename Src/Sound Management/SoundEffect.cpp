#include "SoundEffect.h"

SoundEffect::SoundEffect():
	mSound(nullptr), channel(0)
{
}

SoundEffect::~SoundEffect()
{
	if (mSound != nullptr)
	{
		Mix_FreeChunk(mSound);
		mSound = nullptr;
	}
}

void SoundEffect::Play(int loops)
{
	channel = Mix_PlayChannel(-1, mSound, loops);
}

void SoundEffect::Stop()
{
	Mix_HaltChannel(channel);
}

bool SoundEffect::Playing()
{
	return Mix_Playing(channel);
}

bool SoundEffect::Load(std::string path)
{
	mSound = Mix_LoadWAV(path.c_str());
	if (mSound == nullptr)
	{
		std::cout << "Failed to load " << path << " Error: " << Mix_GetError();
		return false;
	}
	return true;
}
