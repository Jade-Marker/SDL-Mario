#include "CharacterPlayable.h"

CharacterPlayable::CharacterPlayable(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int jumpKey, int rightKey, int leftKey,
	LevelMap* map, float moveSpeed, std::vector<CharacterEnemy*>* const enemiesList, std::string name, float scoreXPos, int initialLives, float frameDelay,
	int initalNumOfFrames, int totalNumOfFrames, int startingFrame, int jumpFrameCount, int jumpStartFrame, int moveFrameCount, int moveStartFrame, int idleFrameCount, int idleStartFrame, 
	float initialJumpForce, float gravity, float jumpForceDecrement, bool screenWrappingEnabled):
	Character(renderer, imagePath, startPosition, map, moveSpeed, initialJumpForce, gravity, jumpForceDecrement, frameDelay, totalNumOfFrames, true, startingFrame, initalNumOfFrames, screenWrappingEnabled),
	mState(IDLE), mScore(0), mEnemiesList(enemiesList), mName(name), mScoreXPos(scoreXPos), mLives(initialLives), 
	JUMP_FRAME_COUNT(jumpFrameCount), JUMP_START_FRAME(jumpStartFrame), MOVE_FRAME_COUNT(moveFrameCount), MOVE_START_FRAME(moveStartFrame), IDLE_FRAME_COUNT(idleFrameCount), IDLE_START_FRAME(idleStartFrame)
{
	mInputMap[JUMP] = jumpKey;
	mInputMap[RIGHT] = rightKey;
	mInputMap[LEFT] = leftKey;

	mJumpSound = new SoundEffect();
	mJumpSound->Load("SFX/jumpSound.ogg");
}

void CharacterPlayable::Render(float xOffset)
{
	int left = mCurrentFrame * mSingleSpriteWidth;

	//Get the portion of the spritesheet you want to draw
	//								{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x + xOffset), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };
	
	if (!mInvulnerable)
	{
		if (mFacingDirection == FACING_RIGHT)
			mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
		else
			mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
	else 
	{
		if (mFacingDirection == FACING_RIGHT)
			mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE, (Uint8)255 * abs(sin(INVULN_MULTIPLIER * mInvulnTimer)), 0.0f);
		else
			mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL, (Uint8)255 * abs(sin(INVULN_MULTIPLIER * mInvulnTimer)), 0.0f);
	}
}

void CharacterPlayable::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	int key = e.key.keysym.sym;

	//Handle any events
	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (key == mInputMap[LEFT])
			mMovingLeft = true;
		else if (key == mInputMap[RIGHT])
			mMovingRight = true;
		break;

	case SDL_KEYUP:
		if (key == mInputMap[LEFT])
			mMovingLeft = false;
		else if (key == mInputMap[RIGHT])
			mMovingRight = false;
		else if (key == mInputMap[JUMP])
			Jump();
		break;
	}
	UpdateState();

	if (mInvulnerable)
	{
		mInvulnTimer -= deltaTime;
		if (mInvulnTimer <= 0.0f)
			mInvulnerable = false;
	}


	Animate();

}

void CharacterPlayable::Animate()
{
	if (mState == JUMPING)
	{
		mCurrentNumOfFrames = JUMP_FRAME_COUNT;
		mCurrentStartFrame = JUMP_START_FRAME;
	}
	else if (mState == MOVING)
	{
		mCurrentNumOfFrames = MOVE_FRAME_COUNT;
		mCurrentStartFrame = MOVE_START_FRAME;
	}
	else
	{
		mCurrentNumOfFrames = IDLE_FRAME_COUNT;
		mCurrentStartFrame = IDLE_START_FRAME;
	}
}

void CharacterPlayable::OnPlayerCollision(CharacterPlayable* player)
{
	std::cout << "Colliding with other player" << std::endl;
}

void CharacterPlayable::SetState(CHARACTERSTATE newState)
{
	mState = newState;
}

CHARACTERSTATE CharacterPlayable::GetState()
{
	return mState;
}

void CharacterPlayable::KillPlayer()
{
	if (!mInvulnerable)
	{
		mLives--;
		mInvulnerable = true;
		mInvulnTimer = INVULNERABILITY_TIME;

		if (mLives <= 0)
			SetState(PLAYER_DEATH);
	}
}

void CharacterPlayable::IncrementScore(int value)
{
	mScore += value;
}

int CharacterPlayable::GetScore()
{
	return mScore;
}

void CharacterPlayable::RenderScoreAndLives(Font* font)
{
	std::string scoreString = mName + ":" + std::to_string(mScore);
	font->DrawString(scoreString, Vector2D(mScoreXPos, SCORE_HEIGHT), Vector2D(0.5f, 0.5f));
	
	std::string livesString = "Lives:" + std::to_string(mLives);
	font->DrawString(livesString, Vector2D(mScoreXPos, LIVES_HEIGHT), Vector2D(0.5f, 0.5f));
}

void CharacterPlayable::UpdateState()
{
	if (mJumping)
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

void CharacterPlayable::HitTile()
{
	Character::HitTile();

	if (mCurrentLevelMap->GetTileAt(mPosition.y / mCurrentLevelMap->GetTileset().tileHeight, (mPosition.x + (mSingleSpriteWidth * 0.5f)) / mCurrentLevelMap->GetTileset().tileWidth) == PLATFORM)
	{
		for (int i = 0; i < mEnemiesList->size(); i++)
		{
			CharacterEnemy* currentEnemy = (*mEnemiesList)[i];
			Vector2D enemyPosition = currentEnemy->GetPosition();

			int playerTileX = (int)mPosition.x / mCurrentLevelMap->GetTileset().tileWidth;
			int playerTileY = (int)mPosition.y / mCurrentLevelMap->GetTileset().tileHeight;
			int enemyTileX = (int)enemyPosition.x / mCurrentLevelMap->GetTileset().tileWidth;
			int enemyTileY = (int)enemyPosition.y / mCurrentLevelMap->GetTileset().tileHeight;

			if (playerTileX == enemyTileX || playerTileX == enemyTileX + 1 || playerTileX == enemyTileX - 1)
			{
				if(enemyTileY == playerTileY - 1)
					currentEnemy->TakeDamage();
			}
		}
	}
}
