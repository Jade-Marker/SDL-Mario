#pragma once

#include <list>
#include "SoundEffect.h"
class SoundList
{
private:
	std::list<SoundEffect*> mSounds;
	static SoundList* mInstance;
	SoundList();

public:
	~SoundList();
	static SoundList* Instance();
	void AddSoundToList(SoundEffect* sound);

	void Update();
};

