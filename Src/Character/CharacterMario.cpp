#include "CharacterMario.h"
#include "GameScreenLevel2.h"

void CharacterMario::HitTile()
{
	int headPosition = (int)(mPosition.y) / mCurrentLevelMap->GetTileset().tileHeight;
	int centralXPosition = (mPosition.x + (mSingleSpriteWidth * 0.5f)) / mCurrentLevelMap->GetTileset().tileWidth;
	int leftXPosition = (mPosition.x + mSingleSpriteWidth * GRAVITY_CHECK_FALLOFF) / mCurrentLevelMap->GetTileset().tileWidth;
	int rightXPosition = (mPosition.x + mSingleSpriteWidth * (1.0f - GRAVITY_CHECK_FALLOFF)) / mCurrentLevelMap->GetTileset().tileWidth;

	bool leftTileState = mCurrentLevelMap->TileIsPassable(mCurrentLevelMap->GetTileAt(headPosition, leftXPosition));
	bool rightTileState = mCurrentLevelMap->TileIsPassable(mCurrentLevelMap->GetTileAt(headPosition, rightXPosition));
	bool middleTileState = mCurrentLevelMap->TileIsPassable(mCurrentLevelMap->GetTileAt(headPosition, centralXPosition));

	int blockingX;
	if ((!leftTileState && !middleTileState) || (!rightTileState && !middleTileState))
	{
		blockingX = centralXPosition;
	}
	else
	{
		if (!leftTileState)
			blockingX = leftXPosition;
		else if (!middleTileState)
			blockingX = centralXPosition;
		else
			blockingX = rightXPosition;
	}

	if (mCurrentLevelMap->GetTileAt(headPosition, blockingX) == (TILE)QMARK_BLOCK)
	{
		mCurrentLevelMap->ChangeTileAt(headPosition, blockingX, (TILE)USED_BLOCK);
		currentLevel->CreateQMarkCoin(Vector2D(blockingX * mCurrentLevelMap->GetTileset().tileWidth, headPosition*mCurrentLevelMap->GetTileset().tileHeight - mCurrentLevelMap->GetTileset().tileHeight));
	}

	Character::HitTile();
}

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int jumpKey, int rightKey, int leftKey,
    LevelMap* map, float moveSpeed, std::vector<CharacterEnemy*>* const enemiesList, std::string name, float scoreXPos, int initialLives,
    float frameDelay, int initalNumOfFrames, int totalNumOfFrames, int startingFrame,
    int jumpFrameCount, int jumpStartFrame, int moveFrameCount, int moveStartFrame, int idleFrameCount, int idleStartFrame,
	float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, std::string jumpSFXPath, GameScreenLevel2* gameScreen, bool screenWrappingEnabled):
    CharacterPlayable(renderer, imagePath, startPosition, jumpKey, rightKey, leftKey,
        map, moveSpeed, enemiesList, name, scoreXPos, initialLives,
        frameDelay, initalNumOfFrames, totalNumOfFrames, startingFrame,
        jumpFrameCount, jumpStartFrame, moveFrameCount, moveStartFrame, idleFrameCount, idleStartFrame,
		initialJumpForce, gravity, jumpForceDecrement, collisionRadius, jumpSFXPath, screenWrappingEnabled), currentLevel(gameScreen)
{
}

void CharacterMario::UpdateState()
{
	if (mJumping || !mCanJump)
	{
		mState = JUMPING;
	}
	else if (mMovingLeft || mMovingRight)
	{
		mState = MOVING;
	}
	else
	{
		mState = IDLE;
	}
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	CharacterPlayable::Update(deltaTime, e);

	if (mPosition.y > mCurrentLevelMap->GetHeight()* mCurrentLevelMap->GetTileset().tileHeight)
		KillPlayer();
}

void CharacterMario::KillPlayer()
{
	mLives--;
	currentLevel->RestartLevel();
}
