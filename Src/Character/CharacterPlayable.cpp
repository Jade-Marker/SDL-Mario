#include "CharacterPlayable.h"

CharacterPlayable::CharacterPlayable(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int jumpKey, int rightKey, int leftKey,
	LevelMap* map, float moveSpeed, std::vector<CharacterEnemy*>* const enemiesList, std::string name, float scoreXPos, int initialLives, float frameDelay,
	int initalNumOfFrames, int totalNumOfFrames, int startingFrame):
	Character(renderer, imagePath, startPosition, map, moveSpeed, frameDelay, totalNumOfFrames, true, startingFrame, initalNumOfFrames),
	mState(IDLE), mScore(0), mEnemiesList(enemiesList), mName(name), mScoreXPos(scoreXPos), mLives(initialLives)
{
	mInputMap[JUMP] = jumpKey;
	mInputMap[RIGHT] = rightKey;
	mInputMap[LEFT] = leftKey;

	mJumpSound = new SoundEffect();
	mJumpSound->Load("SFX/jumpSound.ogg");
}

void CharacterPlayable::Render()
{
	int left = mCurrentFrame * mSingleSpriteWidth;

	//Get the portion of the spritesheet you want to draw
	//								{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };
	
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
		mCurrentNumOfFrames = MARIO_JUMP_FRAME_COUNT;
		mCurrentStartFrame = MARIO_JUMP_START_FRAME;
	}
	else if (mState == MOVING)
	{
		mCurrentNumOfFrames = MARIO_MOVE_FRAME_COUNT;
		mCurrentStartFrame = MARIO_MOVE_START_FRAME;
	}
	else
	{
		mCurrentNumOfFrames = MARIO_IDLE_FRAME_COUNT;
		mCurrentStartFrame = MARIO_IDLE_START_FRAME;
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

	if (mCurrentLevelMap->GetTileAt(mPosition.y / TILE_HEIGHT, (mPosition.x + (mSingleSpriteWidth * 0.5f)) / TILE_WIDTH) == PLATFORM)
	{
		for (int i = 0; i < mEnemiesList->size(); i++)
		{
			CharacterEnemy* currentEnemy = (*mEnemiesList)[i];
			Vector2D enemyPosition = currentEnemy->GetPosition();

			int playerTileX = (int)mPosition.x / TILE_WIDTH;
			int playerTileY = (int)mPosition.y / TILE_HEIGHT;
			int enemyTileX = (int)enemyPosition.x / TILE_WIDTH;
			int enemyTileY = (int)enemyPosition.y / TILE_HEIGHT;

			if (playerTileX == enemyTileX || playerTileX == enemyTileX + 1 || playerTileX == enemyTileX - 1)
			{
				if(enemyTileY == playerTileY - 1)
					currentEnemy->TakeDamage();
			}
		}
	}
}