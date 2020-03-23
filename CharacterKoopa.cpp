#include "CharacterKoopa.h"
#include "CharacterPlayable.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed, float frameDelay, int noOfFrames) :
	CharacterEnemy(renderer, imagePath, startPosition, map, movementSpeed, frameDelay, noOfFrames, false), mInjured(false), mInjuredTime(0)
{
	mFacingDirection = startFacing;
	mCurrentFrame = KOOPA_MOVING_FRAME;
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::TakeDamage()
{
	if (!mInjured)
	{
		mInjured = true;
		mInjuredTime = INJURED_TIME;
		mCurrentFrame = KOOPA_DAMAGED_FRAME;
	}
	else
	{
		FlipRightwayUp();
	}

	Jump();
}

void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;

		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	//To gain the benefit of the code written in the base class Update() function we need to call it
	Character::Update(deltaTime, e);

	if (!mInjured)
	{
		//We are not injured so move
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else 
	{
		//We should not be moving when injured
		mMovingRight = false;
		mMovingLeft = false;

		//Count down the injured time
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
			FlipRightwayUp();
	}
}

void CharacterKoopa::OnPlayerCollision(CharacterPlayable* player)
{
	if (GetInjured())
	{
		SetAlive(false);
		player->IncrementScore(KOOPA_SCORE);
	}
	else
		player->SetState(PLAYER_DEATH);
}

bool CharacterKoopa::GetInjured()
{
	return mInjured;
}

void CharacterKoopa::FlipRightwayUp()
{
	if (mFacingDirection == FACING_RIGHT)
		mFacingDirection = FACING_LEFT;
	else if (mFacingDirection == FACING_LEFT)
		mFacingDirection = FACING_RIGHT;

	mCurrentFrame = KOOPA_MOVING_FRAME;
	mInjured = false;
	Jump();
}
