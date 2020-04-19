#include "CharacterGoomba.h"

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
	float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
	float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, bool screenWrapping):
	CharacterEnemy(renderer, imagePath, startPosition, map, moveSpeed, frameDelay, noOfFrames, animating, startFrame,
		currentNumOfFrames, initialJumpForce, gravity, jumpForceDecrement, collisionRadius, screenWrapping)
{
	mMovingLeft = true;
	mState = GOOMBA_MOVING;

	mHitSound = new SoundEffect();
	mHitSound->Load("SFX/Marioland SFX/stomp.wav");
}

CharacterGoomba::~CharacterGoomba()
{
	delete mHitSound;
}

void CharacterGoomba::Update(float deltaTime, SDL_Event e)
{
	if (mState == GOOMBA_MOVING)
	{
		int leftX = (int)(roundf(mPosition.x) / mCurrentLevelMap->GetTileset().tileWidth);
		int rightX = (int)(roundf(mPosition.x + mSingleSpriteWidth) / mCurrentLevelMap->GetTileset().tileWidth);
		int y = (int)(mPosition.y / mCurrentLevelMap->GetTileset().tileHeight);

		if (mMovingLeft)
		{
			if (!mCurrentLevelMap->TileIsPassable(mCurrentLevelMap->GetTileAt(y, leftX)))
			{
				mMovingLeft = false;
				mMovingRight = true;
			}
		}
		else if (mMovingRight)
		{
			if (!mCurrentLevelMap->TileIsPassable(mCurrentLevelMap->GetTileAt(y, rightX)))
			{
				mMovingLeft = true;
				mMovingRight = false;
			}
		}
	}
	else if (mState == GOOMBA_DEAD)
	{
		mCurrentNumOfFrames = 1;
		mCurrentStartFrame = 2;
		
		mDeadTimer += deltaTime;

		if (mDeadTimer >= 0.5f)
		{
			mAlive = false;
		}
	}
	Character::Update(deltaTime, e);
}

void CharacterGoomba::OnPlayerCollision(CharacterPlayable* player)
{
	if (player->GetPosition().y + player->GetHeight() * 0.6f < mPosition.y && mState != GOOMBA_DEAD)
	{
		//mAlive = false;
		mState = GOOMBA_DEAD;
		mMovingLeft = false;
		mMovingRight = false;
		player->JumpedOnEnemy();
		mHitSound->Play(0);
	}
	else if (mState != GOOMBA_DEAD)
		player->KillPlayer();
}
