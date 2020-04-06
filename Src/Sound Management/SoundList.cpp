#include "SoundList.h"

SoundList* SoundList::mInstance = nullptr;

SoundList::SoundList()
{
	
}

SoundList::~SoundList()
{
	mInstance = nullptr;
}

SoundList* SoundList::Instance()
{
	if (!mInstance)
		mInstance = new SoundList();

	return mInstance;
}

void SoundList::AddSoundToList(SoundEffect* sound)
{
	mSounds.push_back(sound);
}

void SoundList::Update()
{
	for (auto iter = mSounds.begin(); iter != mSounds.end();)
	{
		if (!(*iter)->Playing())
		{
			delete *iter;
			iter = mSounds.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
