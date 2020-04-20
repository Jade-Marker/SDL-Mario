#include "CharacterGoomba.h"

void CharacterGoomba::AliveUpdate(float deltaTime, SDL_Event e)
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

void CharacterGoomba::DeadUpdate(float deltaTime, SDL_Event e)
{
	mCurrentNumOfFrames = MARIOLAND_GOOMBA_DEAD_FRAME_COUNT;
	mCurrentStartFrame = MARIOLAND_GOOMBA_DEAD_START_FRAME;

	CharacterMariolandEnemy::DeadUpdate(deltaTime, e);
}

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
	float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
	float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, bool screenWrapping):
	CharacterMariolandEnemy(renderer, imagePath, startPosition, map, moveSpeed, frameDelay, noOfFrames, animating, startFrame,
		currentNumOfFrames, initialJumpForce, gravity, jumpForceDecrement, collisionRadius, screenWrapping, MARIOLAND_GOOMBA_DEATH_TIMER)
{
	mMovingLeft = true;
	mState = MOVING;

	mHitSound = new SoundEffect();
	mHitSound->Load("SFX/Marioland SFX/stomp.wav");
}

CharacterGoomba::~CharacterGoomba()
{
}