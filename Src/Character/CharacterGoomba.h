#pragma once
#include "CharacterMariolandEnemy.h"

class CharacterGoomba :
	public CharacterMariolandEnemy
{
private:
	virtual void DeadUpdate(float deltaTime, SDL_Event e);

public:
	CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
		float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
		float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, bool screenWrapping);
	~CharacterGoomba();
};

