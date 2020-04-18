#include "CharacterEnemy.h"

CharacterEnemy::CharacterEnemy(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
	float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
	float initialJumpForce, float gravity, float jumpForceDecrement):
	Character(renderer, imagePath, startPosition, map, moveSpeed, initialJumpForce, gravity, jumpForceDecrement,frameDelay, noOfFrames, animating, startFrame, currentNumOfFrames), mAlive(true)
{
}

CharacterEnemy::~CharacterEnemy()
{
	if (mDeathSound)
	{
		mDeathSound->Play(0);
		SoundList::Instance()->AddSoundToList(mDeathSound);
	}
}

void CharacterEnemy::TakeDamage()
{
}

void CharacterEnemy::SetAlive(bool value)
{
	mAlive = value;
}

bool CharacterEnemy::GetAlive()
{
	return mAlive;
}
