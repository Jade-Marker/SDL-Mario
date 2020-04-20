#include "CharacterFly.h"

CharacterFly::CharacterFly(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
	float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
	float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, CharacterPlayable* mario) :
	CharacterEnemy(renderer, imagePath, startPosition, map, moveSpeed, frameDelay, noOfFrames, animating, startFrame,
		currentNumOfFrames, initialJumpForce, gravity, jumpForceDecrement, collisionRadius, false), mMario(mario)
{
	mHitSound = new SoundEffect();
	mHitSound->Load("SFX/Marioland SFX/stomp.wav");

	mDeathSound = new SoundEffect();
	mDeathSound->Load("SFX/Marioland SFX/flyDeath.wav");


	mJumpTimer = 2.0f;
	mJumpDirection = FACING_LEFT;
	mState = FLY_MOVING;
}

void CharacterFly::Update(float deltaTime, SDL_Event e)
{
	if (mState == FLY_MOVING)
	{
		mJumpTimer -= deltaTime;

		if (mJumpTimer <= 0.0f && mCanJump)
		{
			Jump();
			mJumpTimer = 2.0f;

			if (mMario->GetPosition().x > mPosition.x)
			{
				mJumpDirection = FACING_RIGHT;
			}
			else
			{
				mJumpDirection = FACING_LEFT;
			}
		}

		if (!mCanJump)
		{
			if (mJumpDirection == FACING_RIGHT)
				mMovingRight = true;
			else
				mMovingLeft = true;
		}
		else
		{
			mMovingLeft = false;
			mMovingRight = false;
		}
	}
	else if (mState == FLY_DEAD)
	{
		mCurrentNumOfFrames = MARIOLAND_GOOMBA_DEAD_FRAME_COUNT;
		mCurrentStartFrame = MARIOLAND_GOOMBA_DEAD_START_FRAME;

		mDeathTimer -= deltaTime;

		if (mDeathTimer <= 0.0f)
		{
			mAlive = false;
		}
	}
	Character::Update(deltaTime, e);
}

void CharacterFly::OnPlayerCollision(CharacterPlayable* player)
{
	if (player->GetPosition().y + player->GetHeight() * MARIOLAND_GOOMBA_PLAYER_HEIGHT_PROPORTION < mPosition.y && !player->IsJumping() && mState != FLY_DEAD)
	{
		mState = FLY_DEAD;
		mMovingLeft = false;
		mMovingRight = false;
		player->JumpedOnEnemy();
		mHitSound->Play(0);
		mDeathTimer = 3.0f;
	}
	else if (mState != FLY_DEAD)
		player->KillPlayer();
}
