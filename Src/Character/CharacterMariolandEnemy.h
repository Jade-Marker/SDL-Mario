#pragma once
#include "CharacterEnemy.h"
#include "CharacterPlayable.h"

class CharacterMariolandEnemy :
	public CharacterEnemy
{
protected:
	SoundEffect* mHitSound;
	CHARACTERSTATE mState;
	float mDeathTimer;

	const float DEATH_TIME;

	virtual void AliveUpdate(float deltaTime, SDL_Event e);
	virtual void DeadUpdate(float deltaTime, SDL_Event e);

public:
	CharacterMariolandEnemy(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
		float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
		float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, bool screenWrapping = true, float deathTime = 0.0f);
	virtual ~CharacterMariolandEnemy();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void OnPlayerCollision(CharacterPlayable* player);
};

