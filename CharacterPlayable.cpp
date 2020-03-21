#include "CharacterPlayable.h"

CharacterPlayable::CharacterPlayable(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int jumpKey, int rightKey, int leftKey,
	LevelMap* map, float moveSpeed, std::vector<CharacterEnemy*>* const enemiesList, std::string name, float scoreXPos):
	Character(renderer, imagePath, startPosition, map, moveSpeed), mState(IDLE), mScore(0), mEnemiesList(enemiesList), mName(name), mScoreXPos(scoreXPos)
{
	mInputMap[JUMP] = jumpKey;
	mInputMap[RIGHT] = rightKey;
	mInputMap[LEFT] = leftKey;
}

void CharacterPlayable::Render()
{
	if (mFacingDirection == FACING_RIGHT)
		mTexture->Render(mPosition, SDL_FLIP_NONE, 0.0);
	else
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL, 0.0);
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

void CharacterPlayable::IncrementScore(int value)
{
	mScore += value;
}

void CharacterPlayable::RenderScore(Font* font)
{
	std::string output = mName + ":" + std::to_string(mScore);
	font->DrawString(output, Vector2D(mScoreXPos, SCORE_HEIGHT), Vector2D(1.0f, 1.0f));
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
