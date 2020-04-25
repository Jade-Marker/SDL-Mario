#include "CharacterFly.h"

void CharacterFly::AliveUpdate(float deltaTime, SDL_Event e)
{
	mJumpTimer -= deltaTime;

	if (mJumpTimer <= 0.0f && mCanJump)
	{
		Jump();
		mJumpTimer = MARIOLAND_FLY_JUMP_TIME;

		if (mMario->GetPosition().x > mPosition.x)
			mJumpDirection = FACING_RIGHT;
		else
			mJumpDirection = FACING_LEFT;
	}

	if (!mCanJump)
	{
		if (mJumpDirection == FACING_RIGHT)
			mMovingRight = true;
		else if (mJumpDirection == FACING_LEFT)
			mMovingLeft = true;
	}
	else
	{
		mMovingLeft = false;
		mMovingRight = false;
	}
}

void CharacterFly::DeadUpdate(float deltaTime, SDL_Event e)
{
	mCurrentNumOfFrames = MARIOLAND_FLY_DEAD_FRAME_COUNT;
	mCurrentStartFrame = MARIOLAND_FLY_DEAD_START_FRAME;

	CharacterMariolandEnemy::DeadUpdate(deltaTime, e);
}

CharacterFly::CharacterFly(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
	float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
	float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, CharacterPlayable* mario, int scoreWorth) :
	CharacterMariolandEnemy(renderer, imagePath, startPosition, map, moveSpeed, frameDelay, noOfFrames, animating, startFrame,
		currentNumOfFrames, initialJumpForce, gravity, jumpForceDecrement, collisionRadius, false, MARIOLAND_FLY_DEATH_TIMER, scoreWorth), mMario(mario)
{
	mHitSound = new SoundEffect();
	mHitSound->Load("SFX/Marioland SFX/stomp.wav");

	mDeathSound = new SoundEffect();
	mDeathSound->Load("SFX/Marioland SFX/flyDeath.wav");

	mJumpTimer = MARIOLAND_FLY_JUMP_TIME;
	mJumpDirection = FACING_LEFT;
}