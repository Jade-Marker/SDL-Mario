#pragma once

#include "Character.h"
#include "CharacterEnemy.h"
#include "Commons.h"
#include "Texture2D.h"

class CharacterKoopa :
	public CharacterEnemy
{
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mInjured;
	float mInjuredTime;

public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed, float frameDelay, int noOfFrames);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	void Update(float deltaTime, SDL_Event e);
	virtual void OnPlayerCollision(CharacterPlayable* player);
	bool GetInjured();

private:
	void FlipRightwayUp();
};

