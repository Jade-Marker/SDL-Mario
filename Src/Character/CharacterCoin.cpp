#include "CharacterCoin.h"
#include "CharacterPlayable.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING moveDirection, float movementSpeed, float frameDelay, int noOfFrames):
	CharacterEnemy(renderer, imagePath, startPosition, map, movementSpeed, frameDelay, noOfFrames, true, 0, noOfFrames)
{
	if (moveDirection == FACING_LEFT)
		mMovingLeft = true;
	else
		mMovingRight = true;

	mDeathSound = new SoundEffect();
	mDeathSound->Load("SFX/coin.ogg");
}

CharacterCoin::~CharacterCoin()
{
}

void CharacterCoin::OnPlayerCollision(CharacterPlayable* player)
{
	SetAlive(false);
	player->IncrementScore(COIN_SCORE);
}
