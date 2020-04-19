#include "CharacterCoin.h"
#include "CharacterPlayable.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING moveDirection,
	float movementSpeed, float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, float frameDelay, int noOfFrames, std::string deathSFXPath, bool screenWrapping):
	CharacterEnemy(renderer, imagePath, startPosition, map, movementSpeed, frameDelay, noOfFrames, true, 0, noOfFrames, initialJumpForce, gravity, jumpForceDecrement, collisionRadius, screenWrapping)
{
	if (moveDirection == FACING_LEFT)
		mMovingLeft = true;
	else
		mMovingRight = true;

	mDeathSound = new SoundEffect();
	mDeathSound->Load(deathSFXPath);
}

CharacterCoin::~CharacterCoin()
{
}

void CharacterCoin::OnPlayerCollision(CharacterPlayable* player)
{
	SetAlive(false);
	player->IncrementScore(COIN_SCORE);
}
