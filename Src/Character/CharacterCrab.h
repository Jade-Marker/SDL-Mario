#pragma once
#include "CharacterKoopa.h"
#include "CharacterPlayable.h"
#include "CharacterCoin.h"

class CharacterCrab :
	public CharacterKoopa
{
private:
	std::vector<CharacterEnemy*>* mEnemiesVector;
	bool mSpeedUp;

	virtual void FlipRightwayUp();

public:
	CharacterCrab(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing,
		float movementSpeed, float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius,
		float frameDelay, int noOfFrames, int startingFrame, int currentNumOfFrames, std::vector<CharacterEnemy*>* enemies);

	void Update(float deltaTime, SDL_Event e);
	void OnPlayerCollision(CharacterPlayable* player);
	virtual void TakeDamage();
};

