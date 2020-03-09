#pragma once

#include "Character.h"
#include "CharacterEnemy.h"
#include "Commons.h"
#include "Texture2D.h"

class CharacterCoin : public CharacterEnemy
{
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	
	float mFrameDelay;
	int mCurrentFrame;

public:
	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING moveDirection, float movementSpeed);
	~CharacterCoin();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	virtual void OnPlayerCollision(CharacterPlayable* player);
};

