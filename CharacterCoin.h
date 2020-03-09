#pragma once

#include "Character.h"
#include "Commons.h"
#include "Texture2D.h"

class CharacterCoin : public Character
{
private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	
	bool mAlive;
	float mFrameDelay;
	int mCurrentFrame;

public:
	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING moveDirection, float movementSpeed);
	~CharacterCoin();
	void Render();
	void Update(float deltaTime, SDL_Event e);
	virtual void OnPlayerCollision(CharacterPlayable* player);
	void SetAlive(bool value);
	bool GetAlive();
};

