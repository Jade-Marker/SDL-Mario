#pragma once

#include "Character.h"
#include "Commons.h"
#include "Texture2D.h"

class CharacterKoopa :
	public Character
{
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mInjured;
	float mInjuredTime;
	bool mAlive;

public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	virtual void OnPlayerCollision(CharacterPlayable* player);
	void SetAlive(bool value);
	bool GetAlive();
	bool GetInjured();

private:
	void FlipRightwayUp();
};

