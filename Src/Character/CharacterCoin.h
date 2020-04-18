#pragma once

#include "Character.h"
#include "CharacterEnemy.h"
#include "Commons.h"
#include "Texture2D.h"

class CharacterCoin : public CharacterEnemy
{
public:
	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING moveDirection, float movementSpeed,
		float initialJumpForce, float gravity, float jumpForceDecrement, float frameDelay, int noOfFrames);
	~CharacterCoin();
	virtual void OnPlayerCollision(CharacterPlayable* player);
};

