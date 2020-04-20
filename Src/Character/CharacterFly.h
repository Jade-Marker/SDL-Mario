#pragma once
#include "CharacterMariolandEnemy.h"

class CharacterFly :
	public CharacterMariolandEnemy
{
private:
	float mJumpTimer;
	CharacterPlayable* mMario;
	FACING mJumpDirection;

	virtual void AliveUpdate(float deltaTime, SDL_Event e);
	virtual void DeadUpdate(float deltaTime, SDL_Event e);

public:
	CharacterFly(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
		float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
		float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, CharacterPlayable* mario);
};

