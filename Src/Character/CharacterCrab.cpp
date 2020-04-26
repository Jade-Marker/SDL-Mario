#include "CharacterCrab.h"

void CharacterCrab::FlipRightwayUp()
{
	CharacterKoopa::FlipRightwayUp();

	mCurrentNumOfFrames = CRAB_MOVING_FRAME_COUNT;
	if (!mSpeedUp)
	{
		mCurrentStartFrame = CRAB_MOVING_FRAME;
		mCurrentFrame = CRAB_MOVING_FRAME;
	}
	else
	{
		mCurrentStartFrame = CRAB_MOVING_FRAME + CRAB_ANGRY_FRAME_DIFFERENCE;
		mCurrentFrame = CRAB_MOVING_FRAME + CRAB_ANGRY_FRAME_DIFFERENCE;
	}
}

CharacterCrab::CharacterCrab(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing,
	float movementSpeed, float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius,
	float frameDelay, int noOfFrames, int startingFrame, int currentNumOfFrames, std::vector<CharacterEnemy*>* enemies) :
	CharacterKoopa(renderer, imagePath, startPosition, map, startFacing, movementSpeed, initialJumpForce, gravity, jumpForceDecrement, collisionRadius,
		frameDelay, noOfFrames, startingFrame, currentNumOfFrames), mEnemiesVector(enemies), mSpeedUp(false)
{
	mDeathSound->Load("SFX/Crab.ogg");
}

void CharacterCrab::Update(float deltaTime, SDL_Event e)
{
	CharacterKoopa::Update(deltaTime, e);

	int numEnemiesLeft = 0;
	for (int i = 0; i < mEnemiesVector->size(); i++)
	{
		CharacterCoin* coin = dynamic_cast<CharacterCoin*>(mEnemiesVector->at(i));

		if (coin == nullptr)
			numEnemiesLeft++;
	}

	if (numEnemiesLeft == 1)
	{
		if (!mSpeedUp)
		{
			mMovementSpeed *= CRAB_SPEED_MULTIPLIER;
			mSpeedUp = true;

			mCurrentNumOfFrames = CRAB_MOVING_FRAME_COUNT;
			mCurrentStartFrame = CRAB_MOVING_FRAME + CRAB_ANGRY_FRAME_DIFFERENCE;
			mCurrentFrame = CRAB_MOVING_FRAME + CRAB_ANGRY_FRAME_DIFFERENCE;
		}
	}

	if (mInjured)
	{
		if (mCurrentFrame == CRAB_DAMAGED_FRAME + CRAB_DAMAGED_FRAME_COUNT)
		{
			mCurrentNumOfFrames = 1;
			mCurrentStartFrame = CRAB_DAMAGED_FRAME + CRAB_DAMAGED_FRAME_COUNT;
			mCurrentFrame = CRAB_DAMAGED_FRAME + CRAB_DAMAGED_FRAME_COUNT;
		}
	}
}

void CharacterCrab::OnPlayerCollision(CharacterPlayable* player)
{
	if (mInjured)
	{
		SetAlive(false);
		player->IncrementScore(CRAB_SCORE);
	}
	else
		player->KillPlayer();
}

void CharacterCrab::TakeDamage()
{
	CharacterKoopa::TakeDamage();

	if (mInjured)
	{
		mCurrentNumOfFrames = CRAB_DAMAGED_FRAME_COUNT;
		mCurrentStartFrame = CRAB_DAMAGED_FRAME;
		mCurrentFrame = CRAB_DAMAGED_FRAME;
	}
}
