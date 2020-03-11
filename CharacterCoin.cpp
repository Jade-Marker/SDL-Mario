#include "CharacterCoin.h"
#include "CharacterPlayable.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING moveDirection, float movementSpeed, float frameDelay, int noOfFrames):
	CharacterEnemy(renderer, imagePath, startPosition, map, movementSpeed, frameDelay, noOfFrames, true)
{
	mPosition = startPosition;

	mAlive = true;

	if (moveDirection == FACING_LEFT)
		mMovingLeft = true;
	else
		mMovingRight = true;
}

CharacterCoin::~CharacterCoin()
{
}

void CharacterCoin::OnPlayerCollision(CharacterPlayable* player)
{
	SetAlive(false);
	player->IncrementScore(COIN_SCORE);
}
