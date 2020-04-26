#pragma once

#include "Character.h"
#include "CharacterEnemy.h"
#include "Commons.h"
#include "Texture2D.h"

class CharacterKoopa :
	public CharacterEnemy
{
protected:
	bool mInjured;
	float mInjuredTime;

public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing,
		float movementSpeed, float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, float frameDelay, int noOfFrames, int startingFrame, int currentNumOfFrames);
	~CharacterKoopa();
	virtual void TakeDamage();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void OnPlayerCollision(CharacterPlayable* player);

protected:
	virtual void FlipRightwayUp();
};

